#pragma once

#include "expression.h"

namespace textLanguageParser {
namespace ast {

class QRUTILS_EXPORT IndexingExpression : public Expression {
public:
	IndexingExpression(QSharedPointer<Expression> const &table, QSharedPointer<Expression> const &indexer)
		: mTable(table), mIndexer(indexer)
	{
	}

	QSharedPointer<Expression> const &table() const {
		return mTable;
	}

	QSharedPointer<Expression> const &indexer() const {
		return mIndexer;
	}

private:
	QSharedPointer<Expression> mTable;
	QSharedPointer<Expression> mIndexer;
};

}
}
