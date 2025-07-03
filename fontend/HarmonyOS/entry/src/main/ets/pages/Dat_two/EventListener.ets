import { promptAction } from '@kit.ArkUI'

@Entry
@Component
struct EventListener {
  build() {
    Column({ space: 20 }) {
      TextInput({ placeholder: "请输入用户名" })
        .onChange((value)=>{
          promptAction.showToast({
            message:value
          })
        })
      Button("登录").width('100%')
        .onClick(()=>{
          promptAction.showDialog({
            message:"你好"
          })
        })
    }
    .padding(20)
  }
}