#ifndef PLUGIN_KEEPER_HPP_
#define PLUGIN_KEEPER_HPP_

namespace rln {

class MobPlugin;

}

class PluginKeeper {
public:
    PluginKeeper(const rln::MobPlugin& plugin);

    ~PluginKeeper();

private:
    const rln::MobPlugin& plugin_;
};

#endif  // !PLUGIN_KEEPER_HPP_
