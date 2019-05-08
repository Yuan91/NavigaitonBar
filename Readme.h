//
//  ReadMe.h
//  NavigationDemo
//
//  Created by du on 2019/5/7.
//  Copyright © 2019 du. All rights reserved.
//

#ifndef ReadMe_h
#define ReadMe_h
/**
 影响导航栏布局的属性:
 translucent
 edgesForExtendedLayout
 extendedLayoutIncluedsOpaqueBars
 automaticallyAdjustScrollViewInsets | contentInsetAdjustmentBehavior
 
 一.对于各个属性的解读
 1.translucent
 来由:iOS7 导航栏增加了translucent(半透明)效果.
 默认值:YES,体现为毛玻璃效果,可以看到下边的视图.如果设置为NO,导航栏颜色为白色.
 影响:导航栏颜色的设置 和 ViewController 下控件的布局; 同时,对于导航栏的颜色/背景图的设置,也会影响这个属性
 
 iOS中关于透明度的属性:
 transparent 全透明. UINavigationBar和UIView 均不具备这个属性
 opaque 不透明.BOOL值.  UIView的属性, 不会影响导航栏的透明效果
 alpha 透明度. float值. UIView有这个属性,颜色值也会有这属性,所有说alpha值的时候,要区分是说控件的透明度还是颜色值的alpha通道
 opacity 透明度. float值. CALayer 的属性. View.alpha = CALayer.opacity
 
 
 2.edgesForExtendedLayout
 来由: iOS7 ViewController 默认使用 full-Screen 布局,也就是说ViewController的大小 和屏幕大小一致.
 但是开发者可以通过ViewController的edgesForExtendedLayout属性来调整,是否让ViewController延伸到屏幕边缘.
 使用场景:该特性主要是处理,当前界面有导航栏或者tabBar时,ViewController的显示区域问题,例如设置edgesForExtendedLayout为UIRectEdgeNone时,则ViewController不会被导航栏和tabBar 所遮挡.
 默认值为:UIRectEdgeAll
 注意点:只有当ViewController被嵌到别的container view controller中时才会起作用,例如UINavigationController
 
 3.extendedLayoutIncluedsOpaqueBars
 来由:iOS 7启用,在导航栏不透明时,调整ViewController与屏幕的对齐方式. 当导航栏为不透明时,发现ViewController 顶部没有与屏幕顶部对齐,即便设置edgesForExtendedLayout 为UIRectEdgeAll 或者 UIRectEdgeTop 也没有作用,这个时候就需要启用extendedLayoutIncluedsOpaqueBars 属性
 默认值为NO
 使用场景: 当导航栏为不透明时,想要通过edgesForExtendedLayout 调整ViewController 与屏幕的对齐方式时,需要 使用这个属性(设置为YES)

 
 4. automaticallyAdjustScrollViewInsets | contentInsetAdjustmentBehavior
 来源:automaticallyAdjustScrollViewInsets iOS 7启用,iOS 11废弃,默认值是YES
 contentInsetAdjustmentBehavior iOS 11启用,默认值UIScrollViewContentInsetAdjustmentAutomatic. 该属性用来代替automaticallyAdjustScrollViewInsets
 使用场景: ①这两个属性,都是为了解决 透明导航栏时 且scrollView及其子类 是控制器的第一个子视图的时候,scrollView 与 UINavigationController 的对齐问题.
值得注意的是,这个时候,UINavigationController/ViewController/ScrollView 三者的顶部仍然是对齐的,与屏幕顶部保持一致.只是系统调整了 scrollView 的 contentInset(在iOS 11及之后,表现为adjustedContentInset)
 
 ②当导航栏为透明时,ViewController 的第一个子视图不是 ScrollView ,系统并不会调整其位置
 
 ③当导航栏被隐藏时,ViewController 的第一个视图是ScrollView, 也会被自动调整位置
 
 
 二.属性之间的相互影响
 1.从translucent 说起
 设置为YES时:
 ①edgesForExtendedLayout 默认为 UIRectEdgeAll
 ②当scrollView 为ViewController第一个子视图时,系统会调整contentInset使其从导航栏下面显示;如果非scrollView视图,则不会调整. 如果此时,我们想调整scrollView的偏移量可以通过automaticallyAdjustScrollViewInsets | contentInsetAdjustmentBehavior 来设置
 设置为NO时:
 ①edgesForExtendedLayout 默认为 UIRectEdgeLeft | UIRectEdgeRight | UIRectEdgeBottom,不会顶部对齐.
 如果 此时想要设置 ViewController 对齐屏幕顶部,可以通过extendedLayoutIncluedsOpaqueBars
 
 当隐藏导航时,不管translucent 如何设置,对于第一个子视图是scrollView的ViewController系统仍会调整它的偏移量
 
 2.translucent 与 UINavigationBar.backgroundImage 的相关影响
 translucent 默认是YES
 ①当未设置translucent 时,它的值受backgroundImage图片像素点alpha值的影响
 使用[setBackgroundImage:forBarMetrics:] 设置背景图
如果图片中有像素点小于1,系统会推断translucent 为YES
当所有像素点alpha值为1的时候,系统会推断translucent为NO.

 ②系统也会根据translucent的值,也修改backgroundImage的透明度
当translucent为YES时,设置了一个完全不透明的图片,系统会自动修正这个图片并为它添加一个透明度，用于模拟 translucent 效果。
 当translucent为NO时,设置了一个带有透明效果的图片,系统会在这个带有透明效果的图片背后，添加一个不透明的纯色图片用于整体效果的合成.
 这个纯色图片的颜色取决于 barStyle 属性，当属性为 UIBarStyleBlack 时为黑色，当属性为 UIBarStyleDefault 时为白色，如果我们设置了 barTintColor，则以设置的颜色为基准。
 
 参考链接:
 https://www.jianshu.com/p/c8ffb2bdda91
 https://tech.meituan.com/2018/10/25/navigation-transition-solution-and-best-practice-in-meituan.html
 
 */

#endif /* ReadMe_h */
