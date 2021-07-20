#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QMouseEvent>

namespace impl {

	template <typename SpinBoxT, typename ValueT>
	class DragableSpinBox : public QLabel {
		public:
			DragableSpinBox(const QString& labelText, SpinBoxT& buddy)
			: QLabel(labelText)
			, m_Buddy(&buddy) {
				setBuddy(&buddy);
			}

		protected:
			virtual void mouseMoveEvent(QMouseEvent* event) override {
				if (!(event->buttons() & Qt::LeftButton))
					return QLabel::mouseMoveEvent(event);

				if (!m_IsDragging) {
					m_StartDragPos = QCursor::pos();
					m_Value = double(m_Buddy->value());
					m_IsDragging = true;
					QApplication::setOverrideCursor(Qt::BlankCursor);
				}
				else {
					int dragDist = QCursor::pos().x() - m_StartDragPos.x();
					if (dragDist == 0)
						return;

					double dragMultiplier = .25 * m_Buddy->singleStep();
					if (!(event->modifiers() & Qt::ControlModifier))
						dragMultiplier *= 10.0;

					m_Value += dragMultiplier * dragDist;

					m_Buddy->setValue(ValueT(m_Value));

					QCursor::setPos(m_StartDragPos);
				}
			}

			virtual void mouseReleaseEvent(QMouseEvent* event) override {
				if (!m_IsDragging || event->button() != Qt::LeftButton)
					return QLabel::mouseReleaseEvent(event);

				m_IsDragging = false;
				QApplication::restoreOverrideCursor();
			}

		private:
			SpinBoxT* m_Buddy;
			bool m_IsDragging = false;

			QPoint m_StartDragPos;
			double m_Value = 0.0;
	};

	typedef DragableSpinBox<QDoubleSpinBox, double> DragFloat;
	typedef DragableSpinBox<QSpinBox, int> DragInt;

}