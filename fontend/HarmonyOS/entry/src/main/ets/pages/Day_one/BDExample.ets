@Entry
@Component
struct BDExample {
  build() {
    Column() {
      Image($r("app.media.Baidu_icon"))
        .width(200)
      Row() {
        TextInput()
          .borderRadius({
            topLeft: 5,
            bottomLeft: 5
          })
          .layoutWeight(1)
          .border({
            width: { left: 2, top: 2, bottom: 2 },
            color: "#ccc"
          })
          .height(42)

        Button("百度一下")
          .type(ButtonType.Normal)
          .borderRadius({
            topRight: 5,
            bottomRight: 5
          })
          .height(42)
      }
      .padding({
        right: 20,
        left: 20
      })
    }
    .width("100%")
    .height("100%")
  }
}