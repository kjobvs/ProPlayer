#include "MultiNode.h"

USING_NS_CC;

void MultiNode::pushTarget(Node* target,GLubyte startColor,GLubyte endColor)
{
	targets.push_back(target);
	fromOpacity.push_back(startColor);
	toOpacity.push_back(endColor);
}