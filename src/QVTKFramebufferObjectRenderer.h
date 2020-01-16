/**
 * @file   QVTKFramebufferObjectRenderer.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:31:25 2020
 *
 * @brief
 *
 *
 */

#ifndef QVTKFRAMEBUFFEROBJECTRENDERER_H
#define QVTKFRAMEBUFFEROBJECTRENDERER_H

#include <memory>
#include <vector>
#include <mutex>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QUndoStack>
#include <QDir>

#include <vtkActor.h>
#include <vtkCellPicker.h>
#include <vtkCubeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkObject.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class Model;
class QVTKFramebufferObjectItem;
class ProcessingEngine;


class QVTKFramebufferObjectRenderer : public QObject,
				      public QQuickFramebufferObject::Renderer,
				      protected QOpenGLFunctions // OpenGL ES 2.0 API
{
  Q_OBJECT

 public:
  /**
   *
   *
   *
   * @return
   */
  QVTKFramebufferObjectRenderer();

  /**
   *
   *
   * @param processingEngine
   */
  void setProcessingEngine(const std::shared_ptr<ProcessingEngine> processingEngine);

  /**
   *
   *
   * @param item
   */
  virtual void synchronize(QQuickFramebufferObject *item) override;

  /**
   * render()
   *
   */
  virtual void render() override;

  /**
   *
   *
   */
  void openGLInitState();

  /**
   *
   *
   * @param size
   *
   * @return
   */
  QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

  /**
   *
   *
   * @param model
   */
  void addModelActor(const std::shared_ptr<Model> model);

  /**
   *
   *
   *
   * @return
   */
  std::shared_ptr<Model> getSelectedModel() const;

  /**
   *
   *
   *
   * @return
   */
  bool isModelSelected() const;

  /**
   *
   *
   * @param positionX
   */
  void setSelectedModelPositionX(const double positionX);

  /**
   *
   *
   * @param positionY
   */
  void setSelectedModelPositionY(const double positionY);

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

  /**
   *
   *
   */
  void resetCamera();

  /**
   *
   *
   * @param screenX
   * @param screenY
   * @param worldPos
   *
   * @return
   */
  const bool screenToWorld(const int16_t screenX, const int16_t screenY, double worldPos[]);

 Q_SIGNALS:
  void isModelSelectedChanged();

  void selectedModelPositionXChanged();
  void selectedModelPositionYChanged();

 private:
  /**
   * initScene()
   *
   */
  void initScene();

  /**
   *
   *
   */
  void generatePlatform();

  /**
   *
   *
   */
  void updatePlatform();

  /**
   *
   *
   * @param x
   * @param y
   */
  void selectModel(const int16_t x, const int16_t y);

  /**
   *
   *
   */
  void clearSelectedModel();

  /**
   *
   *
   * @param isModelSelected
   */
  void setIsModelSelected(const bool isModelSelected);

  /**
   *
   *
   * @param x1
   * @param y1
   * @param z1
   * @param x2
   * @param y2
   * @param z2
   * @param points
   * @param cells
   */
  void createLine(const double x1, const double y1, const double z1, const double x2, const double y2, const double z2, vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkCellArray> cells);

  /**
   *
   *
   *
   * @return
   */
  std::shared_ptr<Model> getSelectedModelNoLock() const;

  std::shared_ptr<ProcessingEngine> m_processingEngine;
  QVTKFramebufferObjectItem *m_vtkFboItem = nullptr;
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_vtkRenderWindow;
  vtkSmartPointer<vtkRenderer> m_renderer;
  vtkSmartPointer<vtkGenericRenderWindowInteractor> m_vtkRenderWindowInteractor;

  vtkSmartPointer<vtkCellPicker> m_picker;

  std::shared_ptr<Model> m_selectedModel = nullptr;
  vtkSmartPointer<vtkActor> m_selectedActor = nullptr;
  bool m_isModelSelected = false;

  double m_selectedModelPositionX = 0.0;
  double m_selectedModelPositionY = 0.0;

  std::shared_ptr<QMouseEvent> m_mouseLeftButton = nullptr;
  std::shared_ptr<QMouseEvent> m_mouseEvent = nullptr;
  std::shared_ptr<QMouseEvent> m_moveEvent = nullptr;
  std::shared_ptr<QWheelEvent> m_wheelEvent = nullptr;

  vtkSmartPointer<vtkCubeSource> m_platformModel;
  vtkSmartPointer<vtkPolyData> m_platformGrid;
  vtkSmartPointer<vtkActor> m_platformModelActor;
  vtkSmartPointer<vtkActor> m_platformGridActor;

  double m_platformWidth = 400.0;
  double m_platformDepth = 400.0;
  double m_platformHeight = 400.0;
  double m_platformThickness = 4.0;
  double m_gridBottomHeight = 0.15;
  uint16_t m_gridSize = 10;

  double m_camPositionX;
  double m_camPositionY;
  double m_camPositionZ;

  double m_clickPositionZ = 0.0;

  bool m_firstRender = true;

  int m_modelsRepresentationOption = 0;
  double m_modelsOpacity = 1.0;
  bool m_modelsGouraudInterpolation = false;
};

#endif // QVTKFRAMEBUFFEROBJECTRENDERER_H
