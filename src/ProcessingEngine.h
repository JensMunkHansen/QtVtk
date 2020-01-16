/**
 * @file   ProcessingEngine.h
 * @author Jens Munk Hansen <jmh@debian9laptop.parknet.dk>
 * @date   Thu Jan 16 23:57:14 2020
 *
 * @brief
 *
 *
 */
#ifndef PROCESSINGENGINE_H
#define PROCESSINGENGINE_H

#include <array>
#include <cstdint>
#include <vector>
#include <mutex>
#include <memory>

#include <QUrl>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>


class Model;

class ProcessingEngine {
 public:
  /**
   *
   *
   */
  ProcessingEngine();

  /**
   *
   *
   * @param modelFilePath
   *
   * @return
   */
  const std::shared_ptr<Model>& addModel(const QUrl &modelFilePath);

  /**
   *
   *
   * @param model
   */
  void placeModel(Model &model) const;

  /**
   *
   *
   * @param modelsRepresentationOption
   */
  void setModelsRepresentation(const int modelsRepresentationOption) const;

  /**
   *
   *
   * @param modelsOpacity
   */
  void setModelsOpacity(const double modelsOpacity) const;

  /**
   *
   *
   * @param enableGouraudInterpolation
   */
  void setModelsGouraudInterpolation(const bool enableGouraudInterpolation) const;

  /**
   *
   *
   */
  void updateModelsColor() const;

  /**
   *
   *
   * @param modelActor
   *
   * @return
   */
  std::shared_ptr<Model> getModelFromActor(const vtkSmartPointer<vtkActor> modelActor) const;

 private:

  /**
   *
   *
   * @param inputData
   *
   * @return
   */
  vtkSmartPointer<vtkPolyData> preprocessPolydata(const vtkSmartPointer<vtkPolyData> inputData) const;

  std::vector<std::shared_ptr<Model>> m_models;
};

#endif // PROCESSINGENGINE_H
