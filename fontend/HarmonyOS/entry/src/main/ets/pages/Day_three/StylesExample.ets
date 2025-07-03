import { promptAction } from '@kit.ArkUI'

@Entry
@Component
struct StylesExample {
  build() {
    Column({ space: 8 }) {
      Button("支付")
        .type(ButtonType.Normal)
        .commonButton()
      Button("支付")
        .type(ButtonType.Normal)
        .commonButton()
      Button("支付")
        .type(ButtonType.Normal)
        .commonButton()
    }
    .padding(10)
    .width("100%")
    .height("100%")
  }
}

@Styles
//不支持传参
function commonButton() {
  .width("100%")
  .backgroundColor(Color.Green)
  .height(50)
  .borderRadius(10)
  .onClick(() => {
    promptAction.showDialog({
      message: "正在支付"
    })
  })
}