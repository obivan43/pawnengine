#include "DoubleLabelWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace editor::impl {

	DoubleLabelWidget::DoubleLabelWidget(const QString& label, double value, QWidget* parent) : QWidget(parent), m_ValueCache(value) {
		QHBoxLayout* layout = new QHBoxLayout(this);

		m_Label = new QLabel(label, this);
		m_Value = new QDoubleSpinBox(this);

		m_Label->setMinimumWidth(80);

		m_Value->setMinimum(-1000.0);
		m_Value->setMaximum(1000.0);
		m_Value->setSingleStep(0.05);

		m_Value->setValue(m_ValueCache);

		layout->addWidget(m_Label);
		layout->addWidget(m_Value);

		setLayout(layout);

		InitConnections();
	}

	void DoubleLabelWidget::SetMinMax(double min, double max) {
		m_Value->setMinimum(min);
		m_Value->setMaximum(max);
	}

	void DoubleLabelWidget::OnValueChanged(double value) {
		m_ValueCache = value;
		emit ValueChanged(m_ValueCache);
	}

	void DoubleLabelWidget::InitConnections() {
		connect(m_Value, SIGNAL(valueChanged(double)), this, SLOT(OnValueChanged(double)));
	}

	void DoubleLabelWidget::SetValue(double value) {
		m_ValueCache = value;
		m_Value->setValue(m_ValueCache);
	}

}
