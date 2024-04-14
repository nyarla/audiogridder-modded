/*
 * Copyright (c) 2020 Andreas Pohl
 * Licensed under MIT (https://github.com/apohl79/audiogridder/blob/master/COPYING)
 *
 * Author: Andreas Pohl
 */

#ifndef Defaults_hpp
#define Defaults_hpp

#include "Utils.hpp"

namespace e47 {
namespace Defaults {

static constexpr int SERVER_PORT = 55056;
static constexpr int CLIENT_PORT = 55088;
static constexpr int SANDBOX_PLUGIN_PORT = 56056;
static constexpr int PLUGIN_TRAY_PORT = 55055;

static const String SANDBOX_CMD_PREFIX = "sandbox";

static const String SANDBOX_PLUGIN_SOCK = "sandbox-plugin-{n}.sock";
static const String PLUGIN_TRAY_SOCK = "plugin-tray.sock";
static const String SERVER_SOCK = "server-{id}.sock";
static const String WORKER_SOCK = "worker-{id}-{n}.sock";

static constexpr int SCAN_WORKERS = 8;
static constexpr int SCAN_ID_START = 1000;

static constexpr int SCAREA_STEPS = 30;
static constexpr int SCAREA_FULLSCREEN = 0xFFFF;

static constexpr int PLUGIN_CHANNELS_MAX = 64;

static constexpr int PLUGIN_FX_CHANNELS_IN = 30;
static constexpr int PLUGIN_FX_CHANNELS_OUT = 32;
static constexpr int PLUGIN_FX_CHANNELS_SC = 2;

static constexpr int PLUGIN_INST_CHANNELS_IN = 0;
static constexpr int PLUGIN_INST_CHANNELS_OUT = 64;
static constexpr int PLUGIN_INST_CHANNELS_SC = 0;

#if AG_PLUGIN
#if JucePlugin_IsMidiEffect
static constexpr int PLUGIN_CHANNELS_IN = 2;
static constexpr int PLUGIN_CHANNELS_OUT = 2;
static constexpr int PLUGIN_CHANNELS_SC = 0;
#elif JucePlugin_IsSynth
static constexpr int PLUGIN_CHANNELS_IN = PLUGIN_INST_CHANNELS_IN;
static constexpr int PLUGIN_CHANNELS_OUT = PLUGIN_INST_CHANNELS_OUT;
static constexpr int PLUGIN_CHANNELS_SC = PLUGIN_INST_CHANNELS_SC;
#else
static constexpr int PLUGIN_CHANNELS_IN = PLUGIN_FX_CHANNELS_IN;
static constexpr int PLUGIN_CHANNELS_OUT = PLUGIN_FX_CHANNELS_OUT;
static constexpr int PLUGIN_CHANNELS_SC = PLUGIN_FX_CHANNELS_SC;
#endif
#endif

#ifndef JUCE_WINDOWS

static const String SERVER_CONFIG_FILE_OLD = "~/.audiogridderserver";
static const String PLUGIN_CONFIG_FILE_OLD = "~/.audiogridder";
static const String KNOWN_PLUGINS_FILE_OLD = "~/.audiogridderserver.cache";

static const String SERVER_CONFIG_FILE = "~/.config/audiogridder/audiogridderserver{id}.cfg";
static const String SERVERS_STARTUP_FILE = "~/.config/audiogridder/serverstartup.cfg";
static const String PLUGIN_CONFIG_FILE = "~/.config/audiogridder/audiogridderplugin.cfg";
static const String PLUGIN_TRAY_CONFIG_FILE = "~/.config/audiogridder/audiogridderplugintray.cfg";
static const String KNOWN_PLUGINS_FILE = "~/.config/audiogridder/audiogridderserver{id}.cache";
static const String DEAD_MANS_FILE = "~/.config/audiogridder/audiogridderserver{id}.crash";
static const String SCAN_ERROR_FILE = "~/.config/audiogridder/audiogridderserver{id}.scanerror";
static const String SCAN_LAYOUT_ERROR_FILE = "~/.config/audiogridder/audiogridderserver{id}.scanlayout";
static const String PLUGIN_LAYOUTS_FILE = "~/.config/audiogridder/audiogridderserver{id}.layouts";
static const String SERVER_RUN_FILE = "~/.config/audiogridder/audiogridderserver{id}.running";
static const String SERVER_WINDOW_POSITIONS_FILE = "~/.config/audiogridder/audiogridderserver{id}.winpos";
static const String PLUGIN_WINDOW_POSITIONS_FILE = "~/.config/audiogridder/audiogridderplugin.winpos";
static const String PRESETS_DIR =
    File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + "/AudioGridder Presets";
static const String DOMAIN_SOCKETS_DIR = "/tmp/audiogridder-sockets";

#else

static const String SERVER_CONFIG_FILE_OLD =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() + "\\.audiogridderserver";
static const String PLUGIN_CONFIG_FILE_OLD =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() + "\\.audiogridder";
static const String KNOWN_PLUGINS_FILE_OLD =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() + "\\.audiogridderserver.cache";

static const String SERVER_CONFIG_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderserver{id}.cfg";
static const String SERVERS_STARTUP_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\serverstartup.cfg";
static const String PLUGIN_CONFIG_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderplugin.cfg";
static const String PLUGIN_TRAY_CONFIG_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderplugintray.cfg";
static const String KNOWN_PLUGINS_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderserver{id}.cache";
static const String DEAD_MANS_FILE = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
                                     "\\AudioGridder\\audiogridderserver{id}.crash";
static const String SCAN_ERROR_FILE = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
                                      "\\AudioGridder\\audiogridderserver{id}.scanerror";
static const String SCAN_LAYOUT_ERROR_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderserver{id}.scanlayout";
static const String PLUGIN_LAYOUTS_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderserver{id}.layouts";
static const String SERVER_RUN_FILE = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
                                      "\\AudioGridder\\audiogridderserver{id}.running";
static const String SERVER_WINDOW_POSITIONS_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderserver{id}.winpos";
static const String PLUGIN_WINDOW_POSITIONS_FILE =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() +
    "\\AudioGridder\\audiogridderplugin.winpos";
static const String PRESETS_DIR =
    File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + "\\AudioGridder Presets";
static const String DOMAIN_SOCKETS_DIR =
    File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName() + "\\AudioGridder\\sockets";

#endif

enum ConfigFileType {
    ConfigServer,
    ConfigServerStartup,
    ConfigServerRun,
    ConfigPlugin,
    ConfigPluginCache,
    ConfigPluginTray,
    ConfigDeadMan,
    WindowPositionsServer,
    WindowPositionsPlugin,
    ScanError,
    ScanLayoutError,
    PluginLayouts
};

inline String getLogDirName() {
#ifdef JUCE_LINUX
    String path = "~/.cache/audiogridder/log";
#else
    auto sep = File::getSeparatorString();
    String path = FileLogger::getSystemLogFileFolder().getFullPathName();
    path << sep << "AudioGridder";
#endif
    return path;
}

inline String getLogFileName(const String& appName, const String& filePrefix, const String& fileExtension,
                             bool latest = false) {
    auto sep = File::getSeparatorString();
    auto path = getLogDirName();
    path << sep << appName << sep << filePrefix
         << (latest ? "latest" : Time::getCurrentTime().formatted("%Y-%m-%d_%H-%M-%S")) << fileExtension;
    return path;
}

inline String getSentryDbPath() {
    return File::getSpecialLocation(File::tempDirectory).getChildFile("ag_sentrydb").getFullPathName();
}

inline String getSentryCrashpadPath() {
#ifndef AG_SENTRY_CRASHPAD_PATH
#define AG_SENTRY_CRASHPAD_PATH ""
#endif
    String path = AG_SENTRY_CRASHPAD_PATH;

    if (File(path).existsAsFile()) {
        return path;
    }

    String filename = "crashpad_handler";
#if JUCE_WINDOWS
    filename << ".exe";
#endif

    // everything is shipped as bundle on macOS and we are putting crashpad inside, on the other platform lets just
    // check if crashpad exists in the same dir as the executable
    path = File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile)
               .getSiblingFile(filename)
               .getFullPathName();
    if (File(path).existsAsFile()) {
        return path;
    }

#if JUCE_WINDOWS
    // on windows we ship crashpad in the same dirs as the exe files, for plugins we look for it in the tray app folder
    String appName;
#if AG_PLUGIN
    appName = "AudioGridderPluginTray";
#else
    appName = "AudioGridderServer";
#endif
    auto sep = File::getSeparatorString();
    path = File::getSpecialLocation(File::globalApplicationsDirectory).getFullPathName();
    path << sep << appName << sep << filename;
    if (File(path).existsAsFile()) {
        return path;
    }
#endif

#if JUCE_LINUX
    // the install script puts crashpad into /usr/local/bin and later into /usr/local/share/audiogridder
    path = "/usr/local/share/audiogridder/" + filename;
    if (File(path).existsAsFile()) {
        return path;
    }
    path = "/usr/local/bin/" + filename;
    if (File(path).existsAsFile()) {
        return path;
    }
#endif

    return {};
}

inline String getConfigFileName(ConfigFileType type, const std::unordered_map<String, String>& replace = {}) {
    String file;
    String fileOld;
    switch (type) {
        case ConfigServer:
            file = SERVER_CONFIG_FILE;
            fileOld = SERVER_CONFIG_FILE_OLD;
            break;
        case ConfigServerStartup:
            file = SERVERS_STARTUP_FILE;
            break;
        case ConfigPlugin:
            file = PLUGIN_CONFIG_FILE;
            fileOld = PLUGIN_CONFIG_FILE_OLD;
            break;
        case ConfigPluginCache:
            file = KNOWN_PLUGINS_FILE;
            fileOld = KNOWN_PLUGINS_FILE_OLD;
            break;
        case ConfigPluginTray:
            file = PLUGIN_TRAY_CONFIG_FILE;
            break;
        case ConfigServerRun:
            file = SERVER_RUN_FILE;
            break;
        case ConfigDeadMan:
            file = DEAD_MANS_FILE;
            break;
        case WindowPositionsServer:
            file = SERVER_WINDOW_POSITIONS_FILE;
            break;
        case WindowPositionsPlugin:
            file = PLUGIN_WINDOW_POSITIONS_FILE;
            break;
        case ScanError:
            file = SCAN_ERROR_FILE;
            break;
        case ScanLayoutError:
            file = SCAN_LAYOUT_ERROR_FILE;
            break;
        case PluginLayouts:
            file = PLUGIN_LAYOUTS_FILE;
            break;
    }
    if (fileOld.isNotEmpty()) {
        File fOld(fileOld);
        File fNew(file);
        if (fOld.existsAsFile()) {
            setLogTagStatic("defaults");
            logln("migrating config file '" << fileOld << "' to '" << file << "'");
            if (!fNew.exists()) {
                fNew.create();
            }
            fOld.copyFileTo(fNew);
            fOld.deleteFile();
        }
    }
    if (!replace.empty()) {
        for (auto& pair : replace) {
            String src = "{" + pair.first + "}";
            String dst = pair.second;
            // special case "id"
            if (pair.first == "id" && pair.second == "0") {
                dst = "";
            }
            file = file.replace(src, dst);
        }
    }
    return file;
}

inline File getSocketPath(const String& socketName, const std::unordered_map<String, String>& replace = {},
                          bool deleteIfExists = false) {
    File root(DOMAIN_SOCKETS_DIR);

    if (!root.exists()) {
        root.createDirectory();
    }

    String name = socketName;

    if (!replace.empty()) {
        for (auto& pair : replace) {
            name = name.replace("{" + pair.first + "}", pair.second);
        }
    }

    auto file = root.getChildFile(name);

    if (deleteIfExists && file.exists()) {
        file.deleteFile();
    }

    return file;
}

bool unixDomainSocketsSupported() noexcept;

static constexpr int DEFAULT_NUM_OF_BUFFERS = 2;
static constexpr int DEFAULT_NUM_RECENTS = 10;
static constexpr int DEFAULT_LOAD_PLUGIN_TIMEOUT = 15000;

static constexpr uint32 BG_COLOR = 0xff222222;
static constexpr uint32 BG_ACTIVE_COLOR = 0xff323232;
static constexpr uint32 TOOLTIP_BG_COLOR = 0xe0323232;
static constexpr uint32 BUTTON_COLOR = 0xff333333;
static constexpr uint32 SLIDERTRACK_COLOR = 0xffffc13b;
static constexpr uint32 SLIDERTHUMB_COLOR = 0xaaffffff;
static constexpr uint32 SLIDERBG_COLOR = 0xff606060;
static constexpr uint32 ACTIVE_COLOR = 0xffffc13b;
static constexpr uint32 CPU_LOW_COLOR = 0xff00ff00;
static constexpr uint32 CPU_MEDIUM_COLOR = 0xffffff00;
static constexpr uint32 CPU_HIGH_COLOR = 0xffff0000;
static constexpr uint32 PLUGIN_OK_COLOR = 0xff008000;
static constexpr uint32 PLUGIN_NOTCONNECTED_COLOR = 0xff8b0000;
static constexpr uint32 PLUGIN_NOTLOADED_COLOR = 0xff8b4f00;

static const String MDNS_SERVICE_NAME = "_audiogridder._tcp.local.";

struct ThemeInitailizer : Component {
    void initPlugin() {
        auto& lf = getLookAndFeel();
        lf.setUsingNativeAlertWindows(true);
        lf.setColour(AlertWindow::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(ResizableWindow::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(PopupMenu::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(PopupMenu::highlightedBackgroundColourId, Colour(Defaults::ACTIVE_COLOR).withAlpha(0.8f));
        lf.setColour(PopupMenu::highlightedTextColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(TextEditor::backgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(TextButton::buttonColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(ComboBox::backgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(ListBox::backgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(Slider::thumbColourId, Colour(Defaults::SLIDERTHUMB_COLOR));
        lf.setColour(Slider::trackColourId, Colour(Defaults::SLIDERTRACK_COLOR));
        lf.setColour(Slider::backgroundColourId, Colour(Defaults::SLIDERBG_COLOR));
        lf.setColour(FileBrowserComponent::currentPathBoxBackgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(FileBrowserComponent::filenameBoxBackgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(FileBrowserComponent::currentPathBoxArrowColourId, Colour(Defaults::ACTIVE_COLOR));
        lf.setColour(DirectoryContentsDisplayComponent::highlightColourId,
                     Colour(Defaults::ACTIVE_COLOR).withAlpha(0.05f));
        lf.setColour(TooltipWindow::backgroundColourId, Colour(Defaults::TOOLTIP_BG_COLOR));
        if (auto lfv4 = dynamic_cast<LookAndFeel_V4*>(&lf)) {
            lfv4->getCurrentColourScheme().setUIColour(LookAndFeel_V4::ColourScheme::widgetBackground,
                                                       Colour(Defaults::BG_COLOR));
            lfv4->getCurrentColourScheme().setUIColour(LookAndFeel_V4::ColourScheme::highlightedFill, Colours::black);
        }
    }

    void initServer() {
        auto& lf = getLookAndFeel();
        lf.setColour(ResizableWindow::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(PopupMenu::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(TextEditor::backgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(TextButton::buttonColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(ComboBox::backgroundColourId, Colour(Defaults::BUTTON_COLOR));
        lf.setColour(ListBox::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(AlertWindow::backgroundColourId, Colour(Defaults::BG_COLOR));
        lf.setColour(TooltipWindow::backgroundColourId, Colour(Defaults::TOOLTIP_BG_COLOR));
        if (auto lfv4 = dynamic_cast<LookAndFeel_V4*>(&lf)) {
            lfv4->getCurrentColourScheme().setUIColour(LookAndFeel_V4::ColourScheme::widgetBackground,
                                                       Colour(Defaults::BG_COLOR));
        }
    }
};

inline void initPluginTheme() {
    ThemeInitailizer ti;
    ti.initPlugin();
}

inline void initServerTheme() {
    ThemeInitailizer ti;
    ti.initServer();
}

}  // namespace Defaults
}  // namespace e47

#endif /* Defaults_hpp */
