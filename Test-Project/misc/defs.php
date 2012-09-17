<?php

$content = file_get_contents("defs.txt");
$content = preg_replace("#\#define ([^ ]+).+#i", "{OS_TEXT(\"$1\"), $1},", $content);
file_put_contents("defs-out.txt", $content);

