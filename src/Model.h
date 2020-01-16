/**
 * @file   Model.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:53:15 2020
 *
 * @brief
 *
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <mutex>

#include <QObject>
#include <QColor>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkTransformPolyDataFilter.h>


class Model : public QObject {
  Q_OBJECT

 public:
  /**
   *
   *
   * @param modelData
   *
   * @return
   */
  Model(vtkSmartPointer<vtkPolyData> modelData);

  /**
   *
   *
   *
   * @return
   */
  const vtkSmartPointer<vtkActor>& getModelActor() const;

  /**
   *
   *
   *
   * @return
   */
  double getPositionX();

  /**
   *
   *
   *
   * @return
   */
  double getPositionY();

  /**
   *
   *
   * @param x
   * @param y
   */
  void translateToPosition(const double x, const double y);

  /**
   *
   *
   * @param selected
   */
  void setSelected(const bool selected);

  /**
   *
   *
   * @param selectedModelColor
   */
  static void setSelectedModelColor(const QColor &selectedModelColor);

  /**
   *
   *
   *
   * @return
   */
  const double getMouseDeltaX() const;

  /**
   *
   *
   *
   * @return
   */
  const double getMouseDeltaY() const;

  /**
   *
   *
   * @param deltaX
   * @param deltaY
   */
  void setMouseDeltaXY(const double deltaX, const double deltaY);

  /**
   *
   *
   */
  void updateModelColor();

 signals:
  void positionXChanged(const double positionX);
  void positionYChanged(const double positionY);

 private:
  /**
   *
   *
   * @param positionX
   */
  void setPositionX(const double positionX);

  /**
   *
   *
   * @param positionY
   */
  void setPositionY(const double positionY);

  /**
   *
   *
   * @param color
   */
  void setColor(const QColor &color);

  static QColor m_defaultModelColor;
  static QColor m_selectedModelColor;

  vtkSmartPointer<vtkPolyData> m_modelData;
  vtkSmartPointer<vtkPolyDataMapper> m_modelMapper;
  vtkSmartPointer<vtkActor> m_modelActor;

  vtkSmartPointer<vtkTransformPolyDataFilter> m_modelFilterTranslate;

  std::mutex m_propertiesMutex;

  double m_positionX {0.0};
  double m_positionY {0.0};
  double m_positionZ {0.0};

  bool m_selected = false;

  double m_mouseDeltaX = 0.0;
  double m_mouseDeltaY = 0.0;
};

#endif // MODEL_H
