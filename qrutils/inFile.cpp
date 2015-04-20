/* Copyright 2007-2015 QReal Research Group, Dmitry Mordvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "inFile.h"

#include <qrkernel/logging.h>

using namespace utils;

QString InFile::readAll(const QString &fileName, QString *errorString)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QLOG_ERROR() << QString("Opening %1 for read failed: %2").arg(fileName, file.errorString());
		errorString && (*errorString = file.errorString()).isEmpty();
		return QString();
	}

	QTextStream input;
	input.setDevice(&file);
	input.setCodec("UTF-8");
	const QString text = input.readAll();
	file.close();
	errorString && (*errorString = QString()).isEmpty();
	return text;
}
