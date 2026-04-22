#pragma once

// Can be called from any thread. Notifies framework to start unloading after all updates.
void FrameworkRequestUnload();

/// Might run on non-main thread. Called once before framework initialization.
extern "C" void ModBeforeBootstrapInit();

// Might run on non-main thread. Called once after framework deinitialization.
extern "C" void ModAfterBootstrapDeinit();

// Main thread. Called once when framework is initialized.
extern "C" void ModOnLoad();

// Main thread. Called once after ModOnPostUpdate and FrameworkRequestUnload.
extern "C" void ModOnUnload();

// Main thread. Called every frame before any MonoBehaviour::Update.
extern "C" void ModOnUpdate();

// Main thread. Called every frame after all MonoBehaviour::Update.
extern "C" void ModOnPostUpdate();
