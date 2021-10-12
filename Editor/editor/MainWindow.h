#pragma once

#include "PawnEngine/engine/Engine.h"

#include <QtWidgets/QMainWindow>
#include <memory>

namespace editor {

    class MainWindow : public QMainWindow {
            Q_OBJECT

        public:
            static MainWindow* CreateImpl(QApplication* application, QWidget* parent = Q_NULLPTR);

            pawn::engine::Engine* GetEngine() { return m_Engine.get(); }

        protected:
            MainWindow(QWidget* parent);

        protected:
            std::shared_ptr<pawn::engine::Engine> m_Engine;
    };

}
