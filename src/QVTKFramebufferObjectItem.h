/**
 * @file   QVTKFramebufferObjectItem.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:35:12 2020
 *
 * @brief
 *
 *
 */

#ifndef QVTKFRAMEBUFFEROBJECTITEM_H
#define QVTKFRAMEBUFFEROBJECTITEM_H

#include <memory>
#include <queue>
#include <mutex>

#include <QtQuick/QQuickFramebufferObject>

#include "CommandModelTranslate.h"


class CommandModel;
class Model;
class ProcessingEngine;
class QVTKFramebufferObjectRenderer;

class QVTKFramebufferObjectItem : public QQuickFramebufferObject {
  Q_OBJECT

 public:
  /**
   *
   *
   *
   * @return
   */
  QVTKFramebufferObjectItem();

  /**
   *
   *
   *
   * @return
   */
  Renderer *createRenderer() const Q_DECL_OVERRIDE;

  /**
   *
   *
   * @param renderer
   */
  void setVtkFboRenderer(QVTKFramebufferObjectRenderer*  renderer);

  /**
   *
   *
   *
   * @return
   */
  bool isInitialized() const;

  /**
   *
   *
   * @param processingEngine
   */
  void setProcessingEngine(const std::shared_ptr<ProcessingEngine> processingEngine);

  /** @name Model releated functions
   *
   */
  ///@{
  bool isModelSelected() const;

  /**
   *
   *
   *
   * @return
   */
  double getSelectedModelPositionX() const;

  /**
   *
   *
   *
   * @return
   */
  double getSelectedModelPositionY() const;

  void selectModel(const int screenX, const int screenY);

  /**
   *
   *
   *
   * @return
   */
  void resetModelSelection();
  void addModelFromFile(const QUrl &modelPath);

  void translateModel(CommandModelTranslate::TranslateParams_t &translateData, const bool inTransition);
  ///@}

  /** @name Camera related functions
   *
   */
  ///@{

  /**
   *
   *
   *
   * @return
   */
  void wheelEvent(QWheelEvent *e) override;
  /**
   *
   *
   *
   * @return
   */
  void mousePressEvent(QMouseEvent *e) override;
  /**
   *
   *
   *
   * @return
   */
  void mouseReleaseEvent(QMouseEvent *e) override;
  /**
   *
   *
   *
   * @return
   */
  void mouseMoveEvent(QMouseEvent *e) override;

  QMouseEvent *getLastMouseLeftButton();
  QMouseEvent *getLastMouseButton();
  QMouseEvent *getLastMoveEvent();
  QWheelEvent *getLastWheelEvent();

  void resetCamera();
  ///@}

  /**
   *
   *
   *
   * @return
   */
  int getModelsRepresentation() const;
  /**
   *
   *
   *
   * @return
   */
  double getModelsOpacity() const;
  /**
   *
   *
   *
   * @return
   */
  bool getGourauInterpolation() const;
  /**
   *
   *
   *
   * @return
   */
  int getModelColorR() const;
  /**
   *
   *
   *
   * @return
   */
  int getModelColorG() const;
  /**
   *
   *
   *
   * @return
   */
  int getModelColorB() const;

  void setModelsRepresentation(const int representationOption);
  void setModelsOpacity(const double opacity);
  void setGouraudInterpolation(const bool gouraudInterpolation);
  void setModelColorR(const int colorR);
  void setModelColorG(const int colorG);
  void setModelColorB(const int colorB);

  /**
   *
   *
   *
   * @return
   */
  CommandModel* getCommandsQueueFront() const;
  /**
   *
   *
   *
   */
  void commandsQueuePop();
  /**
   *
   *
   *
   * @return
   */
  bool isCommandsQueueEmpty() const;
  void lockCommandsQueueMutex();
  void unlockCommandsQueueMutex();

 signals:
  void rendererInitialized();

  void isModelSelectedChanged();
  void selectedModelPositionXChanged();
  void selectedModelPositionYChanged();

  void addModelFromFileDone();
  void addModelFromFileError(QString error);

 private:
  void addCommand(CommandModel* command);

  QVTKFramebufferObjectRenderer *m_vtkFboRenderer = nullptr;
  std::shared_ptr<ProcessingEngine> m_processingEngine;

  std::queue<CommandModel*> m_commandsQueue;
  std::mutex m_commandsQueueMutex;

  std::shared_ptr<QMouseEvent> m_lastMouseLeftButton;
  std::shared_ptr<QMouseEvent> m_lastMouseButton;
  std::shared_ptr<QMouseEvent> m_lastMouseMove;
  std::shared_ptr<QWheelEvent> m_lastMouseWheel;

  int m_modelsRepresentationOption = 2;
  double m_modelsOpacity = 1.0;
  bool m_gouraudInterpolation = false;
  int m_modelColorR = 3;
  int m_modelColorG = 169;
  int m_modelColorB = 244;
};

#endif // QVTKFRAMEBUFFEROBJECTITEM_H
