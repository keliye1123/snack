
#include "Level.h"

Level::Level(const std::string &LevelName, const std::function<void()> &Init, const std::function<void()> &Input, const std::function<void()> &Update, const std::function<void()> &Render) {
    this -> LevelName = LevelName;
    AddInitLevel_(Init);
    AddInputLevel_(Input);
    AddUpdateLevel_(Update);
    AddRenderLevel_(Render);
}

void Level::AddInitLevel_(const std::function<void()>& Init) {
    this -> InitLevel = Init;
}

void Level::AddInputLevel_(const std::function<void()>& Input) {
    this-> InputLevel = Input;
}

void Level::AddUpdateLevel_(const std::function<void()>& Update) {
    this-> UpdateLevel = Update;
}

void Level::AddRenderLevel_(const std::function<void()>& Render) {
    this-> RenderLevel = Render;
}

void Level::RunInit_() {
    this -> InitLevel();
}

void Level::RunInput_() {
    this -> InputLevel();
}

void Level::RunUpdate_() {
    this -> UpdateLevel();
}

void Level::RunRender_() {
    this -> RenderLevel();
}
