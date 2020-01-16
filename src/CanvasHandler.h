/**
 * @file   CanvasHandler.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Fri Jan 17 00:01:31 2020
 *
 * @brief
 *
 *
 */
#ifndef CANVASHANDLER_H
#define CANVASHANDLER_H

#include <memory>

#include <QObject>
#include <QUrl>


class ProcessingEngine;
class QVTKFramebufferObjectItem;

class CanvasHandler : public QObject {
  Q_OBJECT

  /**
   *
   *
   *
   * @return
   */
  Q_PROPERTY(bool showFileDialog MEMBER m_showFileDialog NOTIFY showFileDialogChanged)

  Q_PROPERTY(bool isModelSelected READ getIsModelSelected NOTIFY isModelSelectedChanged)
  Q_PROPERTY(double modelPositionX READ getSelectedModelPositionX NOTIFY selectedModelPositionXChanged)
  Q_PROPERTY(double modelPositionY READ getSelectedModelPositionY NOTIFY selectedModelPositionYChanged)
 public:
  /**
   *
   *
   * @param argc
   * @param argv
   *
   * @return
   */
  CanvasHandler(int argc, char **argv);

  /**
   *
   *
   * @param path
   */
  Q_INVOKABLE void openModel(const QUrl &path) const;

  Q_INVOKABLE void mousePressEvent(const int button, const int mouseX, const int mouseY) const;
  Q_INVOKABLE void mouseMoveEvent(const int button, const int mouseX, const int mouseY);
  Q_INVOKABLE void mouseReleaseEvent(const int button, const int mouseX, const int mouseY);

  /**
   *
   *
   *
   * @return
   */
  bool getIsModelSelected() const;

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

  Q_INVOKABLE void setModelsRepresentation(const int representationOption);
  Q_INVOKABLE void setModelsOpacity(const double opacity);
  Q_INVOKABLE void setGouraudInterpolation(const bool gouraudInterpolation);
  Q_INVOKABLE void setModelColorR(const int colorR);
  Q_INVOKABLE void setModelColorG(const int colorG);
  Q_INVOKABLE void setModelColorB(const int colorB);
 public slots:
  void startApplication() const;

 signals:
  void showFileDialogChanged();

  void isModelSelectedChanged();
  void selectedModelPositionXChanged();
  void selectedModelPositionYChanged();

 private:
  bool isModelExtensionValid(const QUrl &modelPath) const;

  std::shared_ptr<ProcessingEngine> m_processingEngine;
  QVTKFramebufferObjectItem *m_vtkFboItem = nullptr;
  QObject *m_fileDialog = nullptr;

  double m_previousWorldX = 0;
  double m_previousWorldY = 0;
  bool m_draggingMouse = false;
  bool m_showFileDialog = false;
};

#endif // CANVASHANDLER_H
