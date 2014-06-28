#include <utility>
#include <memory>
#include <iostream>

#include "SceneNode.h"

using namespace std;

SceneNode::SceneNode ()
{
    asset = NULL;
}

SceneNode::~SceneNode()
{

}

void SceneNode::draw()
{
    
    if (asset) {
        // cout << "drawing asset" << endl;
         asset->draw(*this);
    }



    for (int index=0; index< children.size(); ++index)
    {
        children[index]->draw();
    }

}

void SceneNode::addChild(unique_ptr<SceneNode> node)
{
    //auto tnode = unique_ptr<SceneNode>(node);
    children.push_back( move(node) );

}

void SceneNode::setAsset(Model* model)
{
    asset = model;
}

glm::mat4 SceneNode::getMVPMatrix() const
{
    return MVPMatrix;
}
