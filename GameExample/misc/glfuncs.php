<?php

$func_list = array();

function replace($match)
{
    // print_r(func_get_args()); exit;
    $match[0] = trim(preg_replace("#\s+#", " ", $match[0]));
    $res_type = $match[1];
    $func_name = $match[2];
    $params = $match[3];

    switch($res_type){
    case "void":
        $ret_values = 0;
        break;

    case "GLenum":
    case "GLuint":
    case "int":
    case "GLboolean":
    case "GLfloat":
        $ret_values = 1;
        break;

    default:
        if(preg_match("#^(const\s+)?(GLchar|GLvoid|GLuint|GLubyte|GLfloat)\s*\*#", $res_type)){
            echo "skip: $func_name($match[3]))\n";
            return "/* $match[0] */";
        }
        echo "Unknown result type: $res_type\n";
        print_r($match); exit;
    }

    $param_types = array();
    $call_params = array();
    $i = 0;
    $match[3] = trim($match[3]);
    if($match[3] != "void")
    foreach(preg_split("#\s*,\s*#", $match[3]) as $arg){
        $arg_type = preg_replace("#\s*([\w_\d]+)\s*$#", "", $arg);
        // echo "arg type $arg_type\n";
        switch($arg_type){
        case "GLenum":
        case "GLuint":
        case "GLint":
        case "GLclampf":
        case "GLsizeiptr":
        case "GLintptr":
        case "GLbitfield":
        case "GLboolean":
        case "GLsizei":
        case "GLfloat":
        case "GLclampx":
        case "GLubyte":
        case "GLfixed":
            $call_params[] = "($arg_type)os->toNumber(-params+$i)";
            $param_types[] = $arg_type;
            break;

        default:
            if(preg_match("#^(const\s+)?(GLchar|GLvoid|GLuint|GLint|GLubyte|GLfloat|GLsizei|GLboolean|GLfixed)\s*\*"
                . "|GLfloat eqn\["
                . "|GLfixed eqn\["
                . "#", $arg)){
                echo "skip: $func_name($match[3]))\n";
                return "    /* skip: $match[0] */\n\n";
            }
            echo "Unknown arg type: $arg\n";
            print_r($match); exit;
        }
        $i++;
    }
    global $func_list;
    $func_list[] = "    {OS_TEXT(\"$func_name\"), OpenGL::$func_name}";
    $call_params = implode(", ", $call_params);
    $call = "::$func_name($call_params)";
    if($ret_values){
        if($res_type == "GLboolean"){
            $call = "os->pushBool($call ? true : false)";
        }else{
            $call = "os->pushNumber((OS_NUMBER)$call)";
        }
        $call = "$call;\n        return 1";
    }else{
        $call = "$call;\n        return 0";
    }
    $func_def = <<<END
    static int $func_name(OS * os, int params, int, int, void*)
    {
        /* $match[0] */
        $call;
    }\n\n
END;
    return $func_def;
    print_r($match); exit;
}

function indent($content)
{
    // return preg_replace("#^#i", "    ", $content);
    $lines = array();
    foreach(preg_split("#\n#", $content) as $line){
        $lines[] = "    $line";
    }
    return implode("\n", $lines);
}

$content = file_get_contents("glfuncs.txt");
$content = preg_replace_callback("#\s*(?:GL_APICALL\s+|GL_APIENTRY\s+|GL_API\s+)?(.+?)\s+GL_APIENTRY\s*([\w_\d]+)\s*\((.+)\);\s*#i", "replace", $content);
$func_list = implode(",\n", $func_list);
file_put_contents("glfuncs-out.txt", indent(<<<END
struct OpenGL
{
$content
};

OS::FuncDef list[] = {
$func_list,
    {}
};

os->pushGlobals();
os->setFuncs(list);
os->pop();

os->require("opengl");
END
        ));

