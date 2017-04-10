def convert_argv_to_string(argv, node_name_suffix=None):
    output_str = '';

    for arg in argv:
        if node_name_suffix is not None and arg.find('__name') == 0:
            output_str += arg + node_name_suffix + ' '
        else:
            output_str += arg + ' '

    output_str = output_str[:-1]

    return output_str