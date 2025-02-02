/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkCorePythonQtDecorators_h
#define __ctkCorePythonQtDecorators_h

// PythonQt includes
#include <PythonQt.h>

// CTK includes
#include <ctkAbstractJob.h> // For ctkJobDetail
#include <ctkBooleanMapper.h>
#include <ctkUtils.h>
#include <ctkErrorLogContext.h>
#include <ctkWorkflowStep.h>
#include <ctkWorkflowTransitions.h>

// NOTE:
//
// For decorators it is assumed that the methods will never be called
// with the self argument as NULL.  The self argument is the first argument
// for non-static methods.
//

/// \ingroup Core
class ctkCorePythonQtDecorators : public QObject
{
  Q_OBJECT
public:

  ctkCorePythonQtDecorators()
    {
    PythonQt::self()->registerClass(&ctkBooleanMapper::staticMetaObject, "CTKCore");
    PythonQt::self()->registerCPPClass("ctkErrorLogContext", 0, "CTKCore");
    PythonQt::self()->registerCPPClass("ctkJobDetail", 0, "CTKCore");
    PythonQt::self()->registerCPPClass("ctkWorkflowStep", 0, "CTKCore");
    PythonQt::self()->registerClass(&ctkWorkflowInterstepTransition::staticMetaObject, "CTKCore");
    }

public Q_SLOTS:

  //
  // ctkBooleanMapper
  //

  ctkBooleanMapper* new_ctkBooleanMapper(QObject* targetObject, const QByteArray& propertyName, const QByteArray& signal)
    {
    return new ctkBooleanMapper(targetObject, propertyName, signal);
    }

  //
  // ctkWorkflowStep
  //

  ctkWorkflowStep* new_ctkWorkflowStep()
    {
    return new ctkWorkflowStep();
    }

  ctkWorkflowStep* new_ctkWorkflowStep(const QString& newId)
    {
    return new ctkWorkflowStep(newId);
    }

  void delete_ctkWorkflowStep(ctkWorkflowStep * step)
    {
    delete step;
    }

  ctkWorkflow* workflow(ctkWorkflowStep* step)const
    {
    return step->workflow();
    }

  QString id(ctkWorkflowStep* step)const
    {
    return step->id();
    }

  void setId(ctkWorkflowStep* step, const QString& newId)const
    {
    step->setId(newId);
    }

  QString name(ctkWorkflowStep* step)const
    {
    return step->name();
    }

  void setName(ctkWorkflowStep* step, const QString& newName)
    {
    step->setName(newName);
    }

  QString description(ctkWorkflowStep* step)const
    {
    return step->description();
    }

  void setDescription(ctkWorkflowStep* step, const QString& newDescription)
    {
    step->setDescription(newDescription);
    }

  QString statusText(ctkWorkflowStep* step)const
    {
    return step->statusText();
    }

  bool hasValidateCommand(ctkWorkflowStep* step)const
    {
    return step->hasValidateCommand();
    }

  void setHasValidateCommand(ctkWorkflowStep* step, bool newHasValidateCommand)
    {
    step->setHasValidateCommand(newHasValidateCommand);
    }

  bool hasOnEntryCommand(ctkWorkflowStep* step)const
    {
    return step->hasOnEntryCommand();
    }

  void setHasOnEntryCommand(ctkWorkflowStep* step, bool newHasOnEntryCommand)
    {
    step->setHasOnEntryCommand(newHasOnEntryCommand);
    }

  bool hasOnExitCommand(ctkWorkflowStep* step)const
    {
    return step->hasOnExitCommand();
    }

  void setHasOnExitCommand(ctkWorkflowStep* step, bool newHasOnExitCommand)
    {
    step->setHasOnExitCommand(newHasOnExitCommand);
    }

  QObject* ctkWorkflowStepQObject(ctkWorkflowStep* step)
    {
    return step->ctkWorkflowStepQObject();
    }

  //
  // ctkWorkflowInterstepTransition
  //
  ctkWorkflowInterstepTransition* new_ctkWorkflowInterstepTransition(ctkWorkflowInterstepTransition::InterstepTransitionType newTransitionType)
    {
    return new ctkWorkflowInterstepTransition(newTransitionType);
    }

  ctkWorkflowInterstepTransition* new_ctkWorkflowInterstepTransition(ctkWorkflowInterstepTransition::InterstepTransitionType newTransitionType, const QString& newId)
    {
    return new ctkWorkflowInterstepTransition(newTransitionType, newId);
    }

  void delete_ctkWorkflowInterstepTransition(ctkWorkflowInterstepTransition * transition)
    {
    delete transition;
    }

  //
  // ctkErrorLogContext
  //
  ctkErrorLogContext* new_ctkErrorLogContext()
    {
    return new ctkErrorLogContext();
    }

  ctkErrorLogContext* new_ctkErrorLogContext(const QString& msg)
    {
    return new ctkErrorLogContext(msg);
    }

  void setCategory(ctkErrorLogContext* context, const QString& category)
    {
    context->Category = category;
    }
  QString category(ctkErrorLogContext* context)
    {
    return context->Category;
    }

  void setLine(ctkErrorLogContext* context, int line)
    {
    context->Line = line;
    }
  int line(ctkErrorLogContext* context)
    {
    return context->Line;
    }

  void setFile(ctkErrorLogContext* context, const QString& file)
    {
    context->File = file;
    }
  QString file(ctkErrorLogContext* context)
    {
    return context->File;
    }

  void setFunction(ctkErrorLogContext* context, const QString& function)
    {
    context->Function = function;
    }
  QString function(ctkErrorLogContext* context)
    {
    return context->Function;
    }

  void setMessage(ctkErrorLogContext* context, const QString& message)
    {
    context->Message = message;
    }
  QString message(ctkErrorLogContext* context)
    {
    return context->Message;
    }

  //
  // ctkJobDetail
  //
  ctkJobDetail* new_ctkJobDetail()
    {
    return new ctkJobDetail();
    }

  void setJobClass(ctkJobDetail* td, const QString& jobClass)
    {
    td->JobClass = jobClass;
    }
  QString jobClass(ctkJobDetail* td)
    {
    return td->JobClass;
    }

  void setJobUID(ctkJobDetail* td, const QString& jobUID)
    {
    td->JobUID = jobUID;
    }
  QString JobUID(ctkJobDetail* td)
    {
    return td->JobUID;
    }
};

//-----------------------------------------------------------------------------
class PythonQtWrapper_CTKCore : public QObject
{
  Q_OBJECT

public Q_SLOTS:
  QString static_ctkCoreUtils_absolutePathFromInternal(const QString& internalPath, const QString& basePath)
    {
    return ctk::absolutePathFromInternal(internalPath, basePath);
    }

  QString static_ctkCoreUtils_internalPathFromAbsolute(const QString& absolutePath, const QString& basePath)
    {
    return ctk::internalPathFromAbsolute(absolutePath, basePath);
    }
};

//-----------------------------------------------------------------------------
void initCTKCorePythonQtDecorators()
{
  PythonQt::self()->addDecorators(new ctkCorePythonQtDecorators);

  // PythonQt doesn't support wrapping a static function and adding it to the top-level
  // ctk module. This exposes static functions from ctkCoreUtils as ctk.ctkCoreUtils.absolutePathFromInternal(), etc.
  // Note that PythonQtWrapper_CTKCore installs itself as ctk.ctk but using that same module here would replace PythonQtWrapper_CTKCore.
  PythonQt::self()->registerCPPClass("ctkCoreUtils", "", "CTKCore", PythonQtCreateObject<PythonQtWrapper_CTKCore>);
}

#endif
