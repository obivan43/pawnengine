#include "MeshComponentWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor::impl {

	MeshComponentWidget::MeshComponentWidget(QWidget* parent)
		: QWidget(parent)
		, m_Entity(nullptr)
		, m_Mesh(nullptr)
		, m_MeshLineEdit(nullptr)
		, m_MeshLabel(nullptr) {

		QVBoxLayout* layout = new QVBoxLayout(this);

		QHBoxLayout* meshLayout = new QHBoxLayout();

		m_MeshLineEdit = new QLineEdit(this);

		m_MeshLabel = new QLabel("Mesh", this);
		m_MeshLabel->setMinimumWidth(80);

		meshLayout->addWidget(m_MeshLabel);
		meshLayout->addWidget(m_MeshLineEdit);

		layout->addLayout(meshLayout);

		setLayout(layout);

		InitConnections();
	}

	void MeshComponentWidget::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
	}

	void MeshComponentWidget::SetMesh(pawn::engine::MeshComponent* mesh) {
		m_Mesh = mesh;
		m_MeshLineEdit->setText(mesh->MeshName.c_str());
	}

	void MeshComponentWidget::OnLineEditPress() {
		QString& text{ m_MeshLineEdit->text() };

		std::string& meshName{ m_Mesh->MeshName };
		meshName = text.toLocal8Bit().constData();

		emit MeshModified(*m_Entity);
		m_MeshLineEdit->clearFocus();
	}

	void MeshComponentWidget::InitConnections() {
		connect(
			m_MeshLineEdit,
			SIGNAL(returnPressed()),
			this,
			SLOT(OnLineEditPress())
		);
	}

}
