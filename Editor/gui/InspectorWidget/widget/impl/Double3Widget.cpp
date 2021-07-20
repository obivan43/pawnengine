#include "Double3Widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace editor {

	namespace impl {

		Double3Widget::Double3Widget(const QString& label, glm::vec3 value, QWidget* parent) : QWidget(parent), m_ValueCache(value) {
			QHBoxLayout* layout = new QHBoxLayout(this);

			m_Label = new QLabel(label, this);
			m_X = new QDoubleSpinBox(this);
			m_Y = new QDoubleSpinBox(this);
			m_Z = new QDoubleSpinBox(this);

			m_Label->setMinimumWidth(80);

			m_X->setMinimum(-1000.0);
			m_Y->setMinimum(-1000.0);
			m_Z->setMinimum(-1000.0);

			m_X->setMaximum(1000.0);
			m_Y->setMaximum(1000.0);
			m_Z->setMaximum(1000.0);

			m_X->setSingleStep(0.25);
			m_Y->setSingleStep(0.25);
			m_Z->setSingleStep(0.25);

			m_X->setValue(static_cast<double>(m_ValueCache.x));
			m_Y->setValue(static_cast<double>(m_ValueCache.y));
			m_Z->setValue(static_cast<double>(m_ValueCache.z));

			layout->addWidget(m_Label);
			layout->addWidget(m_X);
			layout->addWidget(m_Y);
			layout->addWidget(m_Z);

			setLayout(layout);

			InitConnections();
		}

		void Double3Widget::OnXChanged(double value) {
			m_ValueCache.x = static_cast<float>(value);
			emit ValueChanged(m_ValueCache);
		}
		void Double3Widget::OnYChanged(double value) {
			m_ValueCache.y = static_cast<float>(value);
			emit ValueChanged(m_ValueCache);
		}
		void Double3Widget::OnZChanged(double value) {
			m_ValueCache.z = static_cast<float>(value);
			emit ValueChanged(m_ValueCache);
		}

		void Double3Widget::InitConnections() {
			connect(m_X, SIGNAL(valueChanged(double)), this, SLOT(OnXChanged(double)));
			connect(m_Y, SIGNAL(valueChanged(double)), this, SLOT(OnYChanged(double)));
			connect(m_Z, SIGNAL(valueChanged(double)), this, SLOT(OnZChanged(double)));
		}

		void Double3Widget::SetValue(glm::vec3 value) {
			m_ValueCache = value;
			m_X->setValue(static_cast<double>(m_ValueCache.x));
			m_Y->setValue(static_cast<double>(m_ValueCache.y));
			m_Z->setValue(static_cast<double>(m_ValueCache.z));
		}
	}

}
