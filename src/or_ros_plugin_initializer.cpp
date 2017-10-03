#include <openrave/plugin.h>
#include <boost/bind.hpp>
#include <ros/ros.h>

using namespace OpenRAVE;

namespace armlab_or_plugins
{
    class ORROSPluginInitializer : public ModuleBase
    {
        public:
            ORROSPluginInitializer(EnvironmentBasePtr penv) : ModuleBase(penv)
            {
                __description = "A plugin that parses the input data stream back onto argc and argv, then calls ros::init() with the given data.";
                RegisterCommand("Initialize", boost::bind(&ORROSPluginInitializer::Initialize, this, _1, _2), "Initializes ROS, parsing the input data into argc and argv for ros::init");
            }

        private:
            bool Initialize(std::ostream& sout, std::istream& sinput)
            {
                (void)sout;
                char buffer[512];
                sinput.getline(buffer, 511, '\0');

                std::vector<char *> args;
                std::istringstream string_stream(buffer);

                while(!string_stream.eof())
                {
                    std::string token;
                    string_stream >> token;
                    char* arg = new char[token.size() + 1];
                    std::copy(token.begin(), token.end(), arg);
                    arg[token.size()] = '\0';
                    args.push_back(arg);
                }

                int argc = (int)args.size();
                ros::init(argc, args.data(), "openrave_ros_plugin", ros::init_options::NoSigintHandler);

                for (char* arg: args)
                {
                    delete[] arg;
                }

                return true;
            }
    };
}


// called to create a new plugin
InterfaceBasePtr CreateInterfaceValidated(InterfaceType type, const std::string& interfacename, std::istream& sinput, EnvironmentBasePtr penv)
{
    (void)sinput;
    if (type == PT_Module && interfacename == "orrosplugininitializer")
    {
        return InterfaceBasePtr(new armlab_or_plugins::ORROSPluginInitializer(penv));
    }

    return InterfaceBasePtr();
}

// called to query available plugins
void GetPluginAttributesValidated(PLUGININFO& info)
{
    info.interfacenames[PT_Module].push_back("ORROSPluginInitializer");
}

// called before plugin is terminated
OPENRAVE_PLUGIN_API void DestroyPlugin()
{
}
