/**
 * @file   CommandModelAdd.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:58:47 2020
 *
 * @brief
 *
 *
 */

#ifndef COMMANDMODELADD_H
#define COMMANDMODELADD_H

#include <memory>

#include <QUrl>
#include <QThread>

#include "CommandModel.h"


class Model;
class ProcessingEngine;
class QVTKFramebufferObjectRenderer;

class CommandModelAdd : public QThread, public CommandModel {
  Q_OBJECT

 public:
  /**
   *
   *
   * @param vtkFboRenderer
   * @param processingEngine
   * @param modelPath
   *
   * @return
   */
  CommandModelAdd(QVTKFramebufferObjectRenderer *vtkFboRenderer, std::shared_ptr<ProcessingEngine> processingEngine, QUrl modelPath);

  /**
   *
   *
   */
  void run() Q_DECL_OVERRIDE;

  /**
   *
   *
   *
   * @return
   */
  bool isReady() const override;

  /**
   *
   *
   */
  void execute() override;

 signals:
  void ready();
  void done();

 private:
  std::shared_ptr<ProcessingEngine> m_processingEngine;
  std::shared_ptr<Model> m_model = nullptr;
  QUrl m_modelPath;
  double m_positionX;
  double m_positionY;

  bool m_ready = false;
};

#endif // COMMANDMODELADD_H
