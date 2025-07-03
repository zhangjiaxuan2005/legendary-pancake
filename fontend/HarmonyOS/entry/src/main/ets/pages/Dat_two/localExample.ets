import { promptAction } from '@kit.ArkUI'

@Entry
@ComponentV2
struct LocalExample {
  @Local count: number = 100
  @Local username: string = ""
  @Local password: string = ""

  build() {
    Column({ space: 28 }) {
      Row({ space: 18 }) {
        Button('-')
          .width(50)
          .height(50)
          .onClick(() => {
            this.count--
          })
        Text(this.count.toString())
          .fontSize(24)
        Button('+')
          .width(50)
          .height(50)
          .onClick(() => {
            this.count++
          })

      }
      .width("100%")
      .height(100)
      .justifyContent(FlexAlign.Center)

      Column({ space: 10 }) {
        Image($r("app.media.Baidu_icon"))
          .width(180)
        TextInput({ placeholder: "请输入用户名" })
          .onChange((value) => {
            this.username = value
          })
        TextInput({ placeholder: "请输入密码" })
          .type(InputType.Password)
          .onChange((value) => {
            this.password = value
          })
        Button('登录')
          .onClick(() => {
            if (this.username == "admin" && this.password == "123456") {
              promptAction.showDialog({
                message: "登录成功"
              })
              this.username = ""
              this.password = ""
            } else {
              promptAction.showDialog({
                message: "登录失败"
              })
            }
          })
          .width("100%")
      }
      .width("100%")
      .padding(20)
      .layoutWeight(1)
    }
    .width("100%")
    .height("100%")
  }
}