#include "MyApplication.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"
#include "Utils/UUIDGenerator.hpp"

MyApplication::MyApplication() :
    m_MainWindow(AddWindow({"Window 1"}))
{
    MyLayer& layer = m_MainWindow.GetLayerStack().SetBaseLayer<MyLayer>();
}

MyApplication::~MyApplication() = default;

void MyApplication::Start() {

}

void MyApplication::Update(Saturn::Timestep deltaTime) {

}
