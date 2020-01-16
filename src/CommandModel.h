/**
 * @file   CommandModel.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:56:32 2020
 *
 * @brief
 *
 *
 */

#ifndef COMMANDMODEL_H
#define COMMANDMODEL_H


class QVTKFramebufferObjectRenderer;

class CommandModel {
 public:
  /**
   *
   *
   * @return
   */
  CommandModel() {}

  /**
   *
   *
   *
   */
  virtual ~CommandModel() {}

  /**
   *
   *
   *
   * @return
   */
  virtual bool isReady() const = 0;

  /**
   *
   *
   */
  virtual void execute() = 0;

 protected:
  QVTKFramebufferObjectRenderer *m_vtkFboRenderer;
};

#endif // COMMANDMODEL_H
