#pragma once

#include <qrkernel/ids.h>
#include <qrutils/expressionsParser/number.h>

namespace interpreterBase {
namespace blocksBase {

class BlockParserInterface
{
public:
	virtual ~BlockParserInterface() {}

	virtual utils::Number *standartBlockParseProcess(QString const &stream, int &pos, qReal::Id const &curId) = 0;
	virtual void functionBlockParseProcess(QString const &stream, int &pos, qReal::Id const &curId) = 0;
	virtual void deselect() = 0;
	virtual QMap<QString, utils::Number *> const &variables() const = 0;
};

}
}
