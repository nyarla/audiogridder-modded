/*
 * Copyright (c) 2020 Andreas Pohl
 * Licensed under MIT (https://github.com/apohl79/audiogridder/blob/master/COPYING)
 *
 * Author: Andreas Pohl
 */

#pragma once

#include <JuceHeader.h>
#include <set>

#include "Client.hpp"
#include "Utils.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace e47 {

class AudioGridderAudioProcessor : public AudioProcessor,
                                   public AudioProcessorParameter::Listener,
                                   public LogTagDelegate {
  public:
    AudioGridderAudioProcessor();
    ~AudioGridderAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    bool canAddBus(bool isInput) const override { return isInput == true; }
    bool canRemoveBus(bool isInput) const override { return isInput == true; }
    void numChannelsChanged() override;

    template <typename T>
    void processBlockReal(AudioBuffer<T>& buf, MidiBuffer& midi);

    void processBlock(AudioBuffer<float>& buf, MidiBuffer& midi) override { processBlockReal(buf, midi); }
    void processBlock(AudioBuffer<double>& buf, MidiBuffer& midi) override { processBlockReal(buf, midi); }

    void processBlockBypassed(AudioBuffer<float>& buf, MidiBuffer& midi) override;
    void processBlockBypassed(AudioBuffer<double>& buf, MidiBuffer& midi) override;

    void updateLatency(int samples);

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;
    StringArray getAlternateDisplayNames() const override { return {"AGrid", "AG"}; }

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    bool supportsDoublePrecisionProcessing() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    json getState(bool withServers);
    bool setState(const json& j);

    const String& getMode() const { return m_mode; }

    void updateTrackProperties(const TrackProperties& properties) override {
        traceScope();
        std::lock_guard<std::mutex> lock(m_trackPropertiesMtx);
        m_trackProperties = properties;
    }

    TrackProperties getTrackProperties() {
        traceScope();
        std::lock_guard<std::mutex> lock(m_trackPropertiesMtx);
        return m_trackProperties;
    }

    void loadConfig();
    void loadConfig(const json& j, bool isUpdate = false);
    void saveConfig(int numOfBuffers = -1);

    Client& getClient() { return *m_client; }
    std::vector<ServerPlugin> getPlugins(const String& type) const;
    const std::vector<ServerPlugin>& getPlugins() const { return m_client->getPlugins(); }
    std::set<String> getPluginTypes() const;

    struct LoadedPlugin {
        String id;
        String name;
        String settings;
        StringArray presets;
        Array<Client::Parameter> params;
        bool bypassed = false;
        bool hasEditor = true;
        bool ok = false;
    };

    // Called by the client object to trigger resyncing the remote plugin settings
    void sync();

    enum SyncRemoteMode { SYNC_ALWAYS, SYNC_WITH_EDITOR, SYNC_DISABLED };
    SyncRemoteMode getSyncRemoteMode() const { return m_syncRemote; }
    void setSyncRemoteMode(SyncRemoteMode m) { m_syncRemote = m; }

    // auto& getLoadedPlugins() const { return m_loadedPlugins; }
    int getNumOfLoadedPlugins() {
        std::lock_guard<std::mutex> lock(m_loadedPluginsSyncMtx);
        return (int)m_loadedPlugins.size();
    }
    LoadedPlugin& getLoadedPlugin(int idx) {
        std::lock_guard<std::mutex> lock(m_loadedPluginsSyncMtx);
        return idx > -1 && idx < (int)m_loadedPlugins.size() ? m_loadedPlugins[(size_t)idx] : m_unusedDummyPlugin;
    }

    bool loadPlugin(const ServerPlugin& plugin, String& err);
    void unloadPlugin(int idx);
    String getLoadedPluginsString() const;
    void editPlugin(int idx, int x, int y);
    void hidePlugin(bool updateServer = true);
    int getActivePlugin() const { return m_activePlugin; }
    int getLastActivePlugin() const { return m_lastActivePlugin; }
    bool isEditAlways() const { return m_editAlways; }
    void setEditAlways(bool b) { m_editAlways = b; }
    bool isBypassed(int idx);
    void bypassPlugin(int idx);
    void unbypassPlugin(int idx);
    void exchangePlugins(int idxA, int idxB);
    bool enableParamAutomation(int idx, int paramIdx, int slot = -1);
    void disableParamAutomation(int idx, int paramIdx);
    void getAllParameterValues(int idx);
    void updateParameterValue(int idx, int paramIdx, float val, bool updateServer = true);
    void updateParameterGestureTracking(int idx, int paramIdx, bool starting);
    void increaseSCArea();
    void decreaseSCArea();
    void toggleFullscreenSCArea();

    void storeSettingsA();
    void storeSettingsB();
    void restoreSettingsA();
    void restoreSettingsB();
    void resetSettingsAB();

    bool getMenuShowCategory() const { return m_menuShowCategory; }
    void setMenuShowCategory(bool b) { m_menuShowCategory = b; }
    bool getMenuShowCompany() const { return m_menuShowCompany; }
    void setMenuShowCompany(bool b) { m_menuShowCompany = b; }
    bool getGenericEditor() const { return m_genericEditor; }
    void setGenericEditor(bool b) { m_genericEditor = b; }
    bool getConfirmDelete() const { return m_confirmDelete; }
    void setConfirmDelete(bool b) { m_confirmDelete = b; }
    bool getNoSrvPluginListFilter() const { return m_noSrvPluginListFilter; }
    void setNoSrvPluginListFilter(bool b) { m_noSrvPluginListFilter = b; }
    bool getSrvCanDisableSidechain() const { return m_serverCanDisableSidechain; }
    float getScaleFactor() const { return m_scale; }
    void setScaleFactor(float f) { m_scale = f; }
    bool getCoreDumps() const { return m_coreDumps; }
    void setCoreDumps(bool b) { m_coreDumps = b; }
    Array<ServerPlugin> getRecents();
    void updateRecents(const ServerPlugin& plugin);

    auto& getServers() const { return m_servers; }
    void addServer(const String& s) { m_servers.add(s); }
    void delServer(const String& s);
    String getActiveServerHost() const { return m_client->getServerHostAndID(); }
    String getActiveServerName() const;
    void setActiveServer(const ServerInfo& s);
    Array<ServerInfo> getServersMDNS();
    void setCPULoad(float load);

    int getLatencyMillis() const {
        return (int)lround(m_client->NUM_OF_BUFFERS * getBlockSize() * 1000 / getSampleRate());
    }

    void showMonitor() { m_tray->showMonitor(); }

    String getPresetDir() const { return m_presetsDir; }
    void setPresetDir(const String& d) { m_presetsDir = d; }
    bool hasDefaultPreset() const { return m_defaultPreset.isNotEmpty() && File(m_defaultPreset).existsAsFile(); }
    void storePreset(const File& file);
    bool loadPreset(const File& file);
    void storePresetDefault();
    void resetPresetDefault();

    bool getTransferWhenPlayingOnly() const { return m_transferWhenPlayingOnly; }
    void setTransferWhenPlayingOnly(bool b) { m_transferWhenPlayingOnly = b; }

    // AudioProcessorParameter::Listener
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int, bool) override {}

    // It looks like most hosts do not support dynamic parameter creation or changes to existing parameters. Logic
    // at least allows for the name to be updated. So we create slots at the start.
    class Parameter : public AudioProcessorParameter, public LogTagDelegate {
      public:
        Parameter(AudioGridderAudioProcessor& processor, int slot) : m_processor(processor), m_slotId(slot) {
            setLogTagSource(m_processor.getLogTagSource());
            initAsyncFunctors();
        }
        ~Parameter() override {
            traceScope();
            stopAsyncFunctors();
        }
        float getValue() const override;
        void setValue(float newValue) override;
        float getValueForText(const String& /* text */) const override { return 0; }
        float getDefaultValue() const override { return getParam().defaultValue; }
        String getName(int maximumStringLength) const override;
        String getLabel() const override { return getParam().label; }
        int getNumSteps() const override { return getParam().numSteps; }
        bool isDiscrete() const override { return getParam().isDiscrete; }
        bool isBoolean() const override { return getParam().isBoolean; }
        bool isOrientationInverted() const override { return getParam().isOrientInv; }
        bool isMetaParameter() const override { return getParam().isMeta; }

      private:
        friend AudioGridderAudioProcessor;
        AudioGridderAudioProcessor& m_processor;
        int m_idx = -1;
        int m_paramIdx = 0;
        int m_slotId = 0;

        const LoadedPlugin& getPlugin() const { return m_processor.getLoadedPlugin(m_idx); }
        const Client::Parameter& getParam() const { return getPlugin().params.getReference(m_paramIdx); }

        void reset() {
            m_idx = -1;
            m_paramIdx = 0;
        }

        ENABLE_ASYNC_FUNCTORS();
    };

    class TrayConnection : public InterprocessConnection, public Timer, public LogTagDelegate {
      public:
        std::atomic_bool connected{false};

        TrayConnection(AudioGridderAudioProcessor* p) : LogTagDelegate(p), m_processor(p) {}
        ~TrayConnection() override { disconnect(); }

        void start() { startTimer(500); }

        void connectionMade() override { connected = true; }
        void connectionLost() override { connected = false; }
        void messageReceived(const MemoryBlock& message) override;
        void sendStatus();
        void showMonitor();
        void sendMessage(const PluginTrayMessage& msg);

        void timerCallback() override;

        Array<ServerPlugin> getRecents() {
            std::lock_guard<std::mutex> lock(m_recentsMtx);
            return m_recents;
        }

      private:
        AudioGridderAudioProcessor* m_processor;
        Array<ServerPlugin> m_recents;
        std::mutex m_recentsMtx;
    };

  private:
    Uuid m_instId;
    String m_mode;
    std::unique_ptr<Client> m_client;
    std::unique_ptr<TrayConnection> m_tray;
    std::atomic_bool m_prepared{false};
    std::vector<LoadedPlugin> m_loadedPlugins;
    mutable std::mutex m_loadedPluginsSyncMtx;
    int m_activePlugin = -1;
    int m_lastActivePlugin = -1;
    bool m_editAlways = true;
    StringArray m_servers;
    String m_activeServerFromCfg;
    int m_activeServerLegacyFromCfg;
    String m_presetsDir;
    String m_defaultPreset;

    int m_numberOfAutomationSlots = 16;
    LoadedPlugin m_unusedDummyPlugin;
    Client::Parameter m_unusedParam;

    Array<Array<float>> m_bypassBufferF;
    Array<Array<double>> m_bypassBufferD;
    std::mutex m_bypassBufferMtx;

    String m_settingsA, m_settingsB;

    bool m_menuShowCategory = true;
    bool m_menuShowCompany = true;
    bool m_genericEditor = false;
    bool m_confirmDelete = true;
    bool m_noSrvPluginListFilter = false;
    float m_scale = 1.0;
    bool m_coreDumps = true;

    bool m_transferWhenPlayingOnly = false;

    TrackProperties m_trackProperties;
    std::mutex m_trackPropertiesMtx;

    SyncRemoteMode m_syncRemote = SYNC_WITH_EDITOR;

    // Stay backward compatible: Previously we allocated extra channels for plugins that wanted it, to make them load.
    // Now with sidechain support, we might mess up the input channels, like having a stereo plugin process the
    // sidechain signal on a mono channel. With sidechains we can't do this anymore, but we can't break old sessions
    // either. So for old sessions, we will allow the server deactivate the sidechain.
    bool m_serverCanDisableSidechain = false;

    ENABLE_ASYNC_FUNCTORS();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioGridderAudioProcessor)
};

}  // namespace e47
