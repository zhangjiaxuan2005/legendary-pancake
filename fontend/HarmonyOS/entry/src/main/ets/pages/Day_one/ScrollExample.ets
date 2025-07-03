@Entry
@Component
struct ScrollExample {
  build() {
    Column(){
      Row().width("100%").height(80).backgroundColor(Color.Brown)
      Scroll(){
        Column({space:2}){
          ScrollItem()
          ScrollItem()
          ScrollItem()
          ScrollItem()
          ScrollItem()
          ScrollItem()
          ScrollItem()
          ScrollItem()
        }
      }
      .layoutWeight(1)
      Row().width("100%").height(80).backgroundColor(Color.Brown)
    }
    .width("100%")
    .height("100%")
  }
}

@Component
struct ScrollItem {
  build() {
    Column(){
      Text("ScrollItem")
    }
    .backgroundColor(Color.Pink)
    .justifyContent(FlexAlign.Center)
    .width("100%")
    .height(150)
  }
}