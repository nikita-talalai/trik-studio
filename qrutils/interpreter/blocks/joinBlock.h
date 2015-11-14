/* Copyright 2007-2015 QReal Research Group
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

#pragma once

#include <qrutils/interpreter/block.h>

namespace qReal {
namespace interpretation {
namespace blocks {

/// Implementation of threads join in interpreter. Stops all threads which are different from a thread
/// specidied in a 'Guard' property of the outgoing link. The 'main' thread waits until all other threads
/// arrive at this block, then proceeds to the next block.
class QRUTILS_EXPORT JoinBlock : public Block
{
	Q_OBJECT
public:
	JoinBlock();

	void run() override;

private:
	int mIncomingTokens;
};

}
}
}