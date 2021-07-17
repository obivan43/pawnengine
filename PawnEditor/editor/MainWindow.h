#pragma once

#include "PawnEngine/engine/Engine.h"

#include <QtWidgets/QMainWindow>
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        static MainWindow* CreateImpl(QWidget* parent = Q_NULLPTR);

        pawn::engine::Engine* GetEngine() { return m_Engine.get(); }

    protected:
        MainWindow(QWidget* parent);

    public:
    	bool Running;

    protected:
      std::shared_ptr<pawn::engine::Engine> m_Engine;
};
