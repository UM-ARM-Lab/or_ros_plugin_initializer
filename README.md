# OpenRAVE ROS Initializer
A thin shim to pass commandline/roslaunch arguments to the C++ ros::init function. Includes functionality to append to the plugin name to avoid name conflicts.

# Example usage:
```python
from or_ros_plugin_initializer import ros_argv_conversion
plugin_argv = ros_argv_conversion.convert_argv_to_string(sys.argv, node_name_suffix='_internal_plugin')
ros_initializer = rave.RaveCreateModule(self.env, 'orrosplugininitializer')
ros_initializer.SendCommand('Initialize ' + plugin_argv)
```
