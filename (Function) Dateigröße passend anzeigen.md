Die an die folgenden Funktionen übergebene Zahl wird entsprechend in "Byte","KB","MB","GB","TB" ausgegegeben..

In PHP:

```php
function mysize($size)                      
    {
        $ret=$size;
        $e=array("Byte","KB","MB","GB","TB");
        for($i=0;$i<count($e) && $ret>512;$i++) 
        {
            $ret/=1024;
        }
        return round($ret,2)." ".$e[$i];
    }
```

In C++ :
```c
string mysize(float size) {
  std::stringstream str;
  int i=0;
  float tmp=size;
  string e[5]={"Byte","KB","MB","GB","TB"};
  for(;i<5 && tmp>512;i++) tmp/=1024;
  str<<round(tmp*100)/100<<" "<<e[i];
  return str.str();
}
```


