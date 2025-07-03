@Entry
@ComponentV2
struct TraceAndObserve {
  user: User = new User("张三", 18)

  build() {
    Column() {
      Text(this.user.name)
        .fontSize(18)
      Text(this.user.age.toString())
        .fontSize(18)
      Button("修改姓名")
        .onClick(() => {
          this.user.name = "李四"
          // this.user=new User("李四",19)  @local
        })
    }
    .justifyContent(FlexAlign.Center)
    .width("100%")
    .height("100%")

  }
}


@ObservedV2
class User {
  @Trace name: string
  age: number

  constructor(name: string, age: number) {
    this.name = name
    this.age = age
  }
}