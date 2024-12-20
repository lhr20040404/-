// 处理登录的函数
function handleLogin() {
    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;

    // 检查用户名和密码是否为空
    if (!username || !password) {
        alert('用户名和密码不能为空');
        return;
    }

    // 检查用户名是否为"705"
    if (username === '705' && password) {
        // 登录成功，重定向到首页或其他页面
        window.location.href = 'index.html'; // 根据您的实际情况修改目标页面
    } else {
        // 登录失败，显示错误消息
        alert('用户名或密码错误');
    }
}

// 处理注册的函数
function handleRegister() {
    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;
    var confirmPassword = document.getElementById('confirm-password').value;

    // 检查用户名、密码和确认密码是否为空
    if (!username || !password || !confirmPassword) {
        alert('所有字段不能为空');
        return;
    }

    // 检查密码是否匹配
    if (password !== confirmPassword) {
        alert('密码不匹配');
        return;
    }

    // 注册成功后，重定向到登录页或其他页面
    window.location.href = 'login.html'; // 根据您的实际情况修改目标页面
}