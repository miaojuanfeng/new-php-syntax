##new php syntax:

### in

```
<?php
var_dump("a" in "ab");
var_dump("a" in array("a", "b"));
?>

//Output: bool(true) bool(true)
```

### whether

```
<?php
whether(1){
    echo 1;
}

whether(0){
    echo 0;
}
?>

//Output: 1
```

Like `if` syntax.

### set ... to ...

```
<?php
set "mjf" to a;
echo $a;
?>

//Output: mjf
```

`set "mjf" to a;` as same as `$a = "mjf";`

### get

```
<?php
set "mjf" to a;
echo get a;
?>

//Output: mjf
```
`echo get a;` as same as `echo $a;`
