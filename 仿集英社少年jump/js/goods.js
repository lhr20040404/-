
document.addEventListener('DOMContentLoaded', function () {
    var ticker = document.getElementById('ticker');
    var span = ticker.querySelector('span');

    // 暂停滚动
    function pauseScroll() {
        span.style.animationPlayState = 'paused';
    }

    // 继续滚动
    function resumeScroll() {
        span.style.animationPlayState = 'running';
    }

    // 鼠标悬停时暂停滚动，鼠标离开时继续滚动
    ticker.addEventListener('mouseover', pauseScroll);
    ticker.addEventListener('mouseout', resumeScroll);
});