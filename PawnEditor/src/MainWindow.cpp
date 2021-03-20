#include "pch.h"
#include "MainWindow.h"

#include <string>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Engine(nullptr) {
	setWindowTitle("Pawn Engine Editor");
	setWindowIcon(QIcon(":/pawn.png"));

	m_CentralWidget = CentralWidget::CreateImpl(this);
	m_CentralWidget->setFixedSize(DefaultWidth, DefaultHeight);
	setCentralWidget(m_CentralWidget);

	m_BottomPanel = BottomPanelWidget::CreateImpl(this);
	m_RightPanel = RightPanelWidget::CreateImpl(this);
	m_LeftPanel = LeftPanelWidget::CreateImpl(this);

	addDockWidget(Qt::BottomDockWidgetArea, m_BottomPanel);
	addDockWidget(Qt::RightDockWidgetArea, m_RightPanel);
	addDockWidget(Qt::LeftDockWidgetArea, m_LeftPanel);

	InitConnections();
	InitEngine();
}

void MainWindow::closeEvent(QCloseEvent* event) {
	this->Running = false;
}

void MainWindow::InitEngine() {
	m_Engine.reset(new pawn::Engine);
	m_Engine->Init(m_CentralWidget->GetWindowsHandle(), DefaultWidth, DefaultHeight);

	std::shared_ptr<pawn::Scene>& scene = m_Engine->GetScene();

	m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
	m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

	pawn::Entity entity = scene->CreateEntity("Sphere");
	entity.AddComponent<pawn::MeshComponent>(m_Engine->GetMeshByName("sphere"));

	pawn::Entity camera = scene->CreateEntity("Camera");
	pawn::CameraComponent& cameraComponent = camera.AddComponent<pawn::CameraComponent>();
	cameraComponent.Camera.SetPerspective();
	cameraComponent.IsActiveCamera = true;

	pawn::TransformationComponent& transformationComponent = camera.GetComponent<pawn::TransformationComponent>();
	transformationComponent.Translate(glm::vec3(0.0f, 0.0f, 4.0f));

	emit ActiveSceneChanged(scene);
}

void MainWindow::InitConnections() {
	connect(
		this,
		SIGNAL(ActiveSceneChanged(std::shared_ptr<pawn::Scene>)),
		m_LeftPanel,
		SLOT(OnActiveSceneChanged(std::shared_ptr<pawn::Scene>))
	);

	connect(
		m_LeftPanel,
		SIGNAL(SelectedEntityChanged(pawn::Entity)), 
		m_RightPanel, 
		SLOT(OnSelectedEntityChanged(pawn::Entity))
	);

	connect(
		m_RightPanel,
		SIGNAL(EntityModified()),
		m_LeftPanel, SLOT(OnEntityModified())
	);
}