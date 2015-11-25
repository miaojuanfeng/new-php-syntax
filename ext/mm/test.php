<?php
	//$a = new CI();
	//$a->index();
class a extends CI{
	function __construct(){
		parent::__construct();
		echo "a::__construct\n";
	}
}
$a = new a();
$a->index();
//mm_info();
print_r(get_class_vars('a'));

print_r($a->mmobject);

?>
