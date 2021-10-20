#include "TransformationComponentWidget.h"

#include <QVBoxLayout>

namespace editor::impl {

	TransformationComponentWidget::TransformationComponentWidget(QWidget* parent)
		: QWidget(parent)
		, m_Transformation(nullptr)
		, m_Position(nullptr)
		, m_Rotation(nullptr)
		, m_Scale(nullptr) {
		QVBoxLayout* layout = new QVBoxLayout(this);

		m_Position = new Double3Widget("Position", glm::vec3(0.0f), this);
		m_Rotation = new Double3Widget("Rotation", glm::vec3(0.0f), this);
		m_Scale = new Double3Widget("Scale", glm::vec3(1.0f), this);

		layout->addWidget(m_Position);
		layout->addWidget(m_Rotation);
		layout->addWidget(m_Scale);

		setLayout(layout);

		InitConnections();
	}

	TransformationComponentWidget::TransformationComponentWidget(pawn::engine::TransformationComponent* transformation, QWidget* parent)
		: QWidget(parent)
		, m_Transformation(transformation)
		, m_Position(nullptr)
		, m_Rotation(nullptr)
		, m_Scale(nullptr) {
		QVBoxLayout* layout = new QVBoxLayout(this);

		m_Position = new Double3Widget("Position", m_Transformation->Position, this);
		m_Rotation = new Double3Widget("Rotation", m_Transformation->Rotation, this);
		m_Scale = new Double3Widget("Scale", m_Transformation->Scale, this);

		layout->addWidget(m_Position);
		layout->addWidget(m_Rotation);
		layout->addWidget(m_Scale);

		setLayout(layout);

		InitConnections();
	}

	void TransformationComponentWidget::InitConnections() {
		connect(m_Position, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnPositionChanged(glm::vec3)));
		connect(m_Rotation, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnRotationChanged(glm::vec3)));
		connect(m_Scale, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnScaleChanged(glm::vec3)));
	}

	void TransformationComponentWidget::OnPositionChanged(glm::vec3 value) {
		if (m_Transformation) {
			m_Transformation->Position = value;
		}
	}

	void TransformationComponentWidget::OnRotationChanged(glm::vec3 value) {
		if (m_Transformation) {
			m_Transformation->Rotation = value;
		}
	}

	void TransformationComponentWidget::OnScaleChanged(glm::vec3 value) {
		if (m_Transformation) {
			m_Transformation->Scale = value;
		}
	}

	void TransformationComponentWidget::SetTransformation(pawn::engine::TransformationComponent* transformation) {
		m_Transformation = transformation;
		m_Position->SetValue(m_Transformation->Position);
		m_Rotation->SetValue(m_Transformation->Rotation);
		m_Scale->SetValue(m_Transformation->Scale);
	}

}
