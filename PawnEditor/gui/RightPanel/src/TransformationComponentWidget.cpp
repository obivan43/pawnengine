#include "pch.h"
#include "TransformationComponentWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace impl {

	TransformationComponentWidget::TransformationComponentWidget(QWidget* parent) : QWidget(parent), m_Transformation(nullptr), m_Position(nullptr) {

		m_Position = new Double3Widget("Position", glm::vec3(0.0f), this);

		InitConnections();
	}

	TransformationComponentWidget::TransformationComponentWidget(pawn::TransformationComponent* transformation, QWidget* parent) : QWidget(parent), m_Transformation(transformation), m_Position(nullptr) {
		QVBoxLayout* layout = new QVBoxLayout(this);

		m_Position = new Double3Widget("Position", m_Transformation->Transformation[3], this);
		layout->addLayout(m_Position->layout());

		setLayout(layout);

		InitConnections();
	}

	void TransformationComponentWidget::InitConnections() {
		connect(m_Position, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnPositionChanged(glm::vec3)));
	}

	void TransformationComponentWidget::OnPositionChanged(glm::vec3 value) {
		if (m_Transformation) {
			m_Transformation->Transformation[3][0] = value.x;
			m_Transformation->Transformation[3][1] = value.y;
			m_Transformation->Transformation[3][2] = value.z;
		}
	}

	void TransformationComponentWidget::SetTransformation(pawn::TransformationComponent* transformation) { 
		m_Transformation = transformation;
		m_Position->SetValue(m_Transformation->Transformation[3]);
	}

	QSize TransformationComponentWidget::sizeHint() const {
		QSize default = QWidget::sizeHint();
		return QSize(default.width(), 40);
	}

}