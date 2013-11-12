/*=============================================================================

  Plugin: org.commontk.xnat

  Copyright (c) University College London,
    Centre for Medical Image Computing

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef ctkXnatObject_h
#define ctkXnatObject_h

#include "ctkXNATCoreExport.h"

#include "ctkException.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QMetaType>

class ctkXnatSession;
class ctkXnatObjectPrivate;

#define CTK_XNAT_OBJECT(classType_, baseType_, schemaType_) \
  classType_(const classType_& other) : baseType_(other) { throw ctkRuntimeException("Copy constructor not implemented"); } \
  static const char* staticSchemaType() { return schemaType_; } \
  virtual const char* schemaType() const { return schemaType_; }

//----------------------------------------------------------------------------
/// \ingroup XNATCore
/// ctkXnatObject is the base class of the objects that represent the nodes in
/// the XNAT data hierarchy.
class CTK_XNAT_CORE_EXPORT ctkXnatObject
{

public:

  /// No-op. Throws a ctkRuntimeException
  ctkXnatObject(const ctkXnatObject& other);

  /// Destructs the ctkXnatObject.
  virtual ~ctkXnatObject();

  /// Get the dynamic schema type of object.
  virtual const char* schemaType() const = 0;

  /// Gets the ID of the object.
  QString id() const;

  /// Sets the ID of the object.
  void setId(const QString& id);

  /// Gets the resource URI of the object that can be used to access it through
  /// the REST API.
  virtual QString resourceUri() const = 0;

  /// Gets the name of the object.
  QString name() const;

  /// Sets the name of the object.
  void setName(const QString& name);

  /// Gets the description of the object.
  QString description() const;

  /// Sets the description of the object.
  void setDescription(const QString& description);

  /// Gets the value of the property with the given name.
  QString property(const QString& name) const;

  /// Sets the value of the property with the given name.
  void setProperty(const QString& name, const QVariant& value);

  /// Gets the properties of the object.
  const QMap<QString, QString>& properties() const;

  /// Gets the parent of the object in the data hierarchy. The returned pointer
  /// is 0 for the ctkXnatServer objects and different for any other type of
  /// XNAT objects.
  ctkXnatObject* parent() const;

  /// Sets the parent of the object in the data hierarchy.
  void setParent(ctkXnatObject* parent);

  /// Gets the children of the object.
  QList<ctkXnatObject*> children() const;

  /// Adds an object to the children of the current one.
  void add(ctkXnatObject* child);

  /// Removes the object from the children of the current object and removes it from the XNAT server.
  void remove(ctkXnatObject* child);

  /// Tells if the children and the properties of the objects have been fetched.
  bool isFetched() const;

  /// Resets the object so that its properties and children needs to be fetched
  /// again at the next request.
  virtual void reset();

  /// Fetches the children and the properties of the object.
  void fetch();

  /// Checks if the object exists on the XNAT server.
  bool exists() const;

  /// Creates the object on the XNAT server and sets the new ID.
  void save();

  /// Deletes the object on the XNAT server and removes it from its parent.
  void erase();

  virtual void download(const QString&);
  virtual void upload(const QString&);

  //QObject* asyncObject() const;

  // *********************
  // Add signals for async API
  //Q_SIGNAL downloadFinished(const QString&);

  // *********************
  // SLOTS for async error handling
  //Q_SLOT serverError(XnatError errorType, const QString& message);

  // *********************
  // Add blocking methods
  // throws ctkXnatTimeoutException
  //bool waitForDownloadFinished(const QString&);

protected:

  /// Constructs the ctkXnatObject.
  ctkXnatObject(ctkXnatObject* parent = 0);

  /// Constructs the ctkXnatObject with the given private part.
  ctkXnatObject(ctkXnatObjectPrivate& dd, ctkXnatObject* parent = 0);

  /// Gets the object that represents the connection to the XNAT server
  /// that stores the current object.
  ctkXnatSession* session() const;

  /// The private implementation part of the object.
  const QScopedPointer<ctkXnatObjectPrivate> d_ptr;

private:

  friend class ctkXnatConnection;

  /// The implementation of the fetch mechanism, called by the fetch() function.
  virtual void fetchImpl() = 0;

  Q_DECLARE_PRIVATE(ctkXnatObject)
};

Q_DECLARE_METATYPE(ctkXnatObject*)

#endif
