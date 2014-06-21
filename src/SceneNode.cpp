#include "SceneNode.h"

SceneNode::SceneNode ()
{

}

SceneNode::~SceneNode()
{

}

void SceneNode::draw()
{

    if (asset) {
         asset->draw(*this);
    }



    for (int index=0; index< children.size(); ++index)
    {
        children[index]->draw();
    }

}

void SceneNode::addChild(std::shared_ptr<SceneNode> node)
{
    children.push_back( node);

}

void SceneNode::setAsset(std::shared_ptr<Model> model)
{
    asset = model;
}

glm::mat4 SceneNode::getMVPMatrix() const
{
    return MVPMatrix;
}
