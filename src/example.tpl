
Action= Enum{"merge": 0, "rebase": 1, "commit": 2}

Status= Enum{
  "ok": 0
  "fail": -1
}

Job= {
  "before_script"= [Text]
  "script"= [Text]
  "after_script"= [Text]
  "action"= Action{"undo": 3} | Int{0..3, -1}
}

~<field>= Job

!"stages"= [Text] | [{"name"= Text, "unique"= Bool}]

Remote= {
  "name"= Text
  ~"url"= Text :"localhost"
  "port"= Int{0..60000} :8080
  "username"= Text
  "http-passwd"= Text
}

Remote{
  "name": none
  !"url"
}

"remotes"= [Remote] | [Remote{"port":29418, ~"http-passwd", "proxy"= Text, !"url"}] | Text{a..z} | Null | Empty
