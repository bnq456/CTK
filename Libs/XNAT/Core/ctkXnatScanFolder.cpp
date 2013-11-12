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

#include "ctkXnatScanFolder.h"

#include "ctkXnatSession.h"
#include "ctkXnatExperiment.h"
#include "ctkXnatObjectPrivate.h"
#include "ctkXnatScan.h"

class ctkXnatScanFolderPrivate : public ctkXnatObjectPrivate
{
public:

  ctkXnatScanFolderPrivate()
  : ctkXnatObjectPrivate()
  {
  }

  void reset()
  {
//    uri.clear();
  }

//  QString uri;
};


ctkXnatScanFolder::ctkXnatScanFolder(ctkXnatExperiment* parent)
: ctkXnatObject(*new ctkXnatScanFolderPrivate(), parent)
{
  this->setProperty("ID", "scans");
}

ctkXnatScanFolder::~ctkXnatScanFolder()
{
}

QString ctkXnatScanFolder::resourceUri() const
{
  return QString("%1/%2").arg(parent()->resourceUri(), this->id());
}

void ctkXnatScanFolder::reset()
{
  ctkXnatObject::reset();
}

void ctkXnatScanFolder::fetchImpl()
{
  QString scansUri = this->resourceUri();
  ctkXnatSession* const session = this->session();
  QUuid queryId = session->httpGet(scansUri);

  QList<ctkXnatObject*> scans = session->httpResults(queryId, ctkXnatScan::staticSchemaType());

  foreach (ctkXnatObject* scan, scans)
  {
    this->add(scan);
  }
}
