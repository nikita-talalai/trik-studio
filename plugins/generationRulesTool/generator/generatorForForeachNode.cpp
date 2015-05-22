#include "generatorForForeachNode.h"
#include "generatorForProgramNode.h"
#include "generatorForCallGenerator.h"

#include "ast/identifier.h"
#include "ast/outcomingLinks.h"
#include "ast/program.h"
#include "ast/callGeneratorFor.h"
#include "ast/list.h"
#include "ast/text.h"

#include "plugins/pluginManager/editorManagerInterface.h"

#include "auxiliaryGenerators/listGenerator.h"
#include "auxiliaryGenerators/identifierTypeGenerator.h"

using namespace generationRules::generator;
using namespace simpleParser::ast;

QString GeneratorForForeachNode::generatedResult(QSharedPointer<Foreach> foreachNode
			, GeneratorConfigurer generatorConfigurer)
{
	auto identifierPart = qrtext::as<Identifier>(foreachNode->identifier());
	auto identifierName = identifierPart->name();

	auto listPart = qrtext::as<List>(foreachNode->listPart());
	auto logicalModelInterface = generatorConfigurer.logicalModelInterface();

	auto identifierType = IdentifierTypeGenerator::variableType(listPart);

	qReal::IdList listOfElements = ListGenerator::listOfIds(listPart, logicalModelInterface
			, generatorConfigurer.variablesTable(), generatorConfigurer.currentScope());

	QString result;
	generatorConfigurer.variablesTable().addNewVariable(identifierName, identifierType, listOfElements);

	auto actionNode = foreachNode->program();

	while (generatorConfigurer.variablesTable().nextIdExists(identifierName)) {
		result += resultForOneIteration(actionNode, generatorConfigurer);
		generatorConfigurer.variablesTable().movePointer(identifierName);
	}

	const auto excludedText = qrtext::as<Text>(foreachNode->excludedText());
	if (excludedText) {
		generatorConfigurer.setExcludedText(excludedText->text());
	}
	generatorConfigurer.variablesTable().movePointer(identifierName);
	result += resultForOneIteration(actionNode, generatorConfigurer);
	generatorConfigurer.setExcludedText(QString());

	generatorConfigurer.variablesTable().removeVariable(identifierName);

	return result;
}

QString GeneratorForForeachNode::resultForOneIteration(QSharedPointer<Node> actionNode, GeneratorConfigurer generatorConfigurer)
{
	QString result = "";
	if (actionNode->is<Program>()) {
		result = GeneratorForProgramNode::generatedResult(qrtext::as<Program>(actionNode), generatorConfigurer);
	} else {
		if (actionNode->is<CallGeneratorFor>()) {
			result = GeneratorForCallGenerator::generatedResult(qrtext::as<CallGeneratorFor>(actionNode), generatorConfigurer);
		}
	}

	return result;
}
