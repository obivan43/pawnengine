#pragma once

#include "glm.hpp"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDoubleSpinBox>

namespace editor::impl {

	class DoubleLabelWidget : public QWidget {
			Q_OBJECT

		public:
			DoubleLabelWidget(const QString& label, double value, QWidget* parent = Q_NULLPTR);

			void SetValue(double value);
			void SetMinMax(double min, double max);

		private:
			void InitConnections();

		private slots:
			void OnValueChanged(double value);

		signals:
			void ValueChanged(double);

		private:
			QLabel* m_Label;
			QDoubleSpinBox* m_Value;
			double m_ValueCache;
	};

}
