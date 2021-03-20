#include "pch.h"
#include "MainWindow.h"

#include <string>

#include "gtc/matrix_transform.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Engine(nullptr) {
	setWindowTitle("Pawn Engine Editor");
	setWindowIcon(QIcon(":/pawn.png"));

	m_CentralWidget = CentralWidget::CreateImpl(this);
	m_CentralWidget->setFixedSize(DefaultWidth, DefaultHeight);
	setCentralWidget(m_CentralWidget);

	m_BottomPanel = BottomPanelWidget::CreateImpl(this);
	m_RightPanel = RightPanelWidget::CreateImpl(this);

	addDockWidget(Qt::BottomDockWidgetArea, m_BottomPanel);
	addDockWidget(Qt::RightDockWidgetArea, m_RightPanel);

	InitEngine();

	m_LeftPanel = LeftPanelWidget::CreateImpl(m_Engine->GetScene(), this);
	addDockWidget(Qt::LeftDockWidgetArea, m_LeftPanel);

	connect(m_LeftPanel, SIGNAL(SelectedEntityChanged(pawn::Entity)), m_RightPanel, SLOT(OnSelectedEntityChanged(pawn::Entity)));
	connect(m_RightPanel, SIGNAL(EntityModified()), m_LeftPanel, SLOT(OnEntityModified()));
}

void MainWindow::closeEvent(QCloseEvent* event) {
	this->Running = false;
}

void MainWindow::InitEngine() {
	m_Engine.reset(new pawn::Engine);
	m_Engine->Init(m_CentralWidget->GetWindowsHandle(), DefaultWidth, DefaultHeight);

	m_Engine->UploadMeshFromFile("res\\assets\\models\\cube.obj");
	m_Engine->UploadMeshFromFile("res\\assets\\models\\sphere.obj");

	pawn::Entity entity = m_Engine->GetScene()->CreateEntity("Sphere");
	entity.AddComponent<pawn::MeshComponent>(m_Engine->GetMeshByName("sphere"));

	pawn::Entity camera = m_Engine->GetScene()->CreateEntity("Camera");
	pawn::CameraComponent& cameraComponent = camera.AddComponent<pawn::CameraComponent>();
	cameraComponent.m_Camera.SetPerspective();
	cameraComponent.m_IsActiveCamera = true;

	pawn::TransformationComponent& transformationComponent = camera.GetComponent<pawn::TransformationComponent>();
	transformationComponent.m_Transformation = glm::translate(transformationComponent.m_Transformation, glm::vec3(0.0f, 0.0f, 4.0f));
}