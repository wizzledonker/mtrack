#include "main_window.h"
#include "../project/project.h"
#include "../models/projectitem_model.h"

MainWindow::MainWindow(BaseObjectType* window, const Glib::RefPtr<Gtk::Builder> &gladeRef) : Gtk::ApplicationWindow(window), m_builder(gladeRef) {
  Gtk::GLArea *glArea;

  // We've started the main window - create some new project properties
  m_project = std::make_unique<Project>();
  m_playbackManager = std::make_unique<PlaybackManager>();

  m_playbackManager->signal_source_changed().connect(sigc::mem_fun(*this, &MainWindow::on_playback_source_change));
  m_playbackManager->signal_playback().connect(sigc::mem_fun(*this, &MainWindow::on_playback_status_changed));

  // Set callback handlers
  m_builder->get_widget("importMediaBtn", m_importMediaBtn);
  m_builder->get_widget("projectPropertiesBtn", m_projectPropertiesBtn);
  m_builder->get_widget("aboutBtn", m_aboutBtn);
  m_builder->get_widget_derived("display_area", m_contextManager, m_project.get());
  m_builder->get_widget("mediaIconView", m_mediaItems);

  // Playback widget
  m_builder->get_widget("nextFrameBtn", m_nextFrameBtn);
  m_builder->get_widget("prevFrameBtn", m_prevFrameBtn);
  m_builder->get_widget("lastFrameBtn", m_lastFrameBtn);
  m_builder->get_widget("firstFrameBtn", m_firstFrameBtn);
  m_builder->get_widget("playBtn", m_playBtn);
  m_builder->get_widget("stopBtn", m_stopBtn);
  m_builder->get_widget("playbackWidget", m_playbackWidget);

  // Timeline widget
  m_builder->get_widget_derived("timelineDrawingArea", m_timeline, m_project.get());

  // Set up models
  m_mediaListStore = Gtk::ListStore::create(m_mediaModel);
  m_mediaItems->set_model(m_mediaListStore);
  m_mediaItems->set_text_column(1);
  m_mediaItems->set_pixbuf_column(2);

  m_mediaItems->signal_item_activated().connect(sigc::mem_fun(*this, &MainWindow::on_media_icon_select));
  m_mediaItems->signal_drag_data_get().connect(sigc::mem_fun(*this, &MainWindow::on_media_drag_drop));

  // Set the media items list as a drag source
  this->setup_drag_drop();

  Gtk::MenuItem *m_quitBtn;
  m_builder->get_widget("quitBtn", m_quitBtn);

  // Signal handlers for menu buttons
  m_quitBtn->signal_activate().connect(sigc::ptr_fun(Gtk::Main::quit));
  m_importMediaBtn->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_import_media));
  m_projectPropertiesBtn->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_project_properties));
  m_aboutBtn->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_about));

  m_nextFrameBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_next_frame));
  m_prevFrameBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_prev_frame));
  m_firstFrameBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_first_frame));
  m_lastFrameBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_last_frame));
  m_playBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_play));
  m_stopBtn->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_stop));
  
}

void MainWindow::setup_drag_drop() {
  // Construct an array of targets for the particular drag targets that are supported
  std::vector<Gtk::TargetEntry> dragTargets;
  dragTargets.push_back(Gtk::TargetEntry("PROJECT_ITEM"));

  //m_mediaItems->drag_source_set(dragTargets);
  m_mediaItems->enable_model_drag_source(dragTargets);
  m_timeline->drag_dest_set(dragTargets);
}

void MainWindow::on_media_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection_data, guint info, guint time) {
  // Pass a pointer
  Gtk::TreePath dragLoc = m_mediaItems->get_selected_items().front();
  
  int mediaIndex = get_media_from_path(dragLoc);
  m_timeline->setCurrentDragMedia(mediaIndex);

  // Send drag data, for the benefit of other programs accepting drags
  selection_data.set(selection_data.get_target(), 8, (const guchar*) m_project->getMediaById(mediaIndex)->getName().c_str(), m_project->getMediaById(mediaIndex)->getName().size());
}

// Playback widget
void MainWindow::on_next_frame() {
	m_playbackManager->next();
}

void MainWindow::on_prev_frame() {
	m_playbackManager->prev();
}

void MainWindow::on_first_frame() {
	m_playbackManager->first();
}

void MainWindow::on_last_frame() {
	m_playbackManager->last();
}

void MainWindow::on_play() {
	if (!m_playbackManager->isPlaying()) {
		m_playbackManager->play();
	}
	else {
		m_playbackManager->pause();
	}
}

void MainWindow::on_stop() {
	m_playbackManager->stop();
}

void MainWindow::on_playback_status_changed(bool playing) {
  if (!playing) {
    m_playBtn->set_stock_id(Gtk::Stock::MEDIA_PLAY);
  } else {
    m_playBtn->set_stock_id(Gtk::Stock::MEDIA_PAUSE);
  }
}

int MainWindow::get_media_from_path(const Gtk::TreeModel::Path& path) {
  Gtk::TreeModel::iterator iter = m_mediaItems->get_model()->get_iter(path);
  Gtk::TreeModel::Row selectedRow = *iter;
  return selectedRow[m_mediaModel.m_col_id];
}

void MainWindow::on_media_icon_select(const Gtk::TreeModel::Path& path) {
  // Get the project ID of the media that was selected
  int itemId = get_media_from_path(path);

  m_contextManager->render_media(m_project->getMediaById(itemId));

  m_playbackManager->clearSource();
  m_playbackSource = std::make_unique<MediaPlaybackSource>(m_project->getMediaById(itemId), m_contextManager);
  m_playbackManager->setSource(m_playbackSource.get());

  m_project->setSelectedMedia(itemId);
}

void MainWindow::on_playback_source_change(bool loaded) {
	m_playbackWidget->set_sensitive(loaded);
}

void MainWindow::on_about() {
  Gtk::Dialog *aboutDialog;

  m_builder->get_widget("aboutDialog", aboutDialog);
  int response = aboutDialog->run();

  if (response != GTK_RESPONSE_NONE) aboutDialog->hide();
}

void MainWindow::on_project_properties() {
  Gtk::Dialog *propDialog;

  // Run the project properties dialog
  m_builder->get_widget("projectPropertiesDialog", propDialog);

  Gtk::SpinButton *hres;
  Gtk::SpinButton *vres;
  Gtk::SpinButton *fps;
  Gtk::ColorButton *color;

  // Load all of the fields from the dialog
  m_builder->get_widget("projectHResolution", hres);
  m_builder->get_widget("projectVResolution", vres);
  m_builder->get_widget("projectFPS", fps);
  m_builder->get_widget("projectBgColor", color);
  
  hres->set_value(m_project->getSettings().hResolution);
  vres->set_value(m_project->getSettings().vResolution);
  fps->set_value(m_project->getSettings().fRate);
  color->set_rgba(m_project->getSettings().color);

  int result = propDialog->run();
  if (result == Gtk::RESPONSE_APPLY) {
    // Apply the changed project settings
    m_project->getSettings().hResolution = hres->get_value();
    m_project->getSettings().vResolution = vres->get_value();
    m_project->getSettings().fRate = fps->get_value();
    m_project->getSettings().color = color->get_rgba();

    // Update the resolution in view
    m_contextManager->redisplay();
  }
  propDialog->hide();
}

void MainWindow::on_import_media() {
  Gtk::FileChooserDialog dialog("Please choose a media file",
  Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Import", Gtk::RESPONSE_OK);

  //On windows, the thread isn't stopped, so we make sure it does.
  if (m_playbackManager->hasSource()) m_playbackManager->stop(); 
  int result = dialog.run();
  
  if (result == Gtk::RESPONSE_OK) {
    // Create a new ProjectItem and load the media assosciated with it
    std::unique_ptr<ProjectItem> item = std::make_unique<VideoItem>(dialog.get_file()->get_basename());

    // Load the texture assosciated with the media file into the context manager
    std::string loadError;
    item->load_media(dialog.get_filename(), m_contextManager, loadError);

    // Render the first frame of the item using the contextmanager. TODO: Create custom playback widget and set there
    if (item->isLoaded()) {
      Gtk::TreeModel::iterator modelit = m_mediaListStore->append();
      Gtk::TreeModel::Row newRow = *modelit;
      newRow[m_mediaModel.m_col_name] = item->getName();
      newRow[m_mediaModel.m_col_icon] = item->get_pixbuf();

      m_contextManager->render_media(item.get());

      m_playbackManager->clearSource();
      m_playbackSource = std::make_unique<MediaPlaybackSource>(item.get(), m_contextManager);
      m_playbackManager->setSource(m_playbackSource.get());

      int mediaIndex = m_project->importMedia(std::move(item));
      newRow[m_mediaModel.m_col_id] = mediaIndex;
    } else {
      Gtk::MessageDialog unableToOpenMsg(*this, "Error loading media file");
      unableToOpenMsg.set_secondary_text(loadError);
      unableToOpenMsg.run();
    }
  }
}

MainWindow::~MainWindow() {}
