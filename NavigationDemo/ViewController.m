//
//  ViewController.m
//  NavigationDemo
//
//  Created by du on 2019/4/14.
//  Copyright © 2019 du. All rights reserved.
//

#import "ViewController.h"
#import "Masonry.h"
@interface ViewController () <UITableViewDelegate,UITableViewDataSource>

@property (nonatomic,strong) UITableView *tableView;

@end

@implementation ViewController

/*
 1.translucent
 来由:iOS7 导航栏增加了translucent(半透明)效果.
 默认值:YES,体现为毛玻璃效果,可以看到下边的视图.如果设置为NO,导航栏颜色为白色.
 影响:导航栏颜色的设置 和 ViewController 下scroll 的布局
 
 
 
 
1.edgesForExtendedLayout
 来由: iOS7 ViewController 默认使用 full-Screen 布局,也就是说ViewController的大小 和屏幕大小一致.
 但是开发者可以通过ViewController的edgesForExtendedLayout属性来调整,是否让ViewController延伸到屏幕边缘.
 使用场景:该特性主要是处理,当前界面有导航栏或者tabBar时,ViewController的显示区域问题,例如设置edgesForExtendedLayout为UIRectEdgeNone时,则ViewController不会被导航栏和tabBar 所遮挡.
 默认值为:UIRectEdgeAll
 注意点:只有当ViewController被嵌到别的container view controller中时才会起作用,例如UINavigationController
 相互影响的属性:
 
 
 2.
 
 
 */

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"First";
    self.view.backgroundColor = [UIColor purpleColor];
    

    self.navigationController.navigationBar.translucent = YES;
    
    //self.navigationController.navigationBar.translucent = YES; 修改导航栏的颜色
    [self.navigationController.navigationBar setBackgroundColor:[UIColor redColor]];

    
//    UIView *redView = [UIView new];
//    redView.backgroundColor = [UIColor redColor];
//    [self.view addSubview:redView];
//    [redView mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.left.right.top.equalTo(self.view);
//        make.height.equalTo(@200);
//    }];
//    return;
    
    _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    _tableView.delegate = self;
    _tableView.dataSource = self;
    _tableView.tableFooterView = [[UIView alloc] init];
    _tableView.rowHeight = 50;
    [self.view addSubview:self.tableView];
    [self.tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return 10;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    cell.textLabel.text = [NSString stringWithFormat:@"我是第%d行",(indexPath.row + 1)];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}



@end
