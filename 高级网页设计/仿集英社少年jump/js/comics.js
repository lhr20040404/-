
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

// lazy-load.js
document.addEventListener('DOMContentLoaded', function() {
    const images = document.querySelectorAll('img[data-src]');
  
    images.forEach(img => {
      const src = img.getAttribute('data-src');
      img.src = src;
      img.removeAttribute('data-src'); // 加载后移除data-src属性
    });
  });

  // image-preview.js
  //图片预览
document.querySelectorAll('img').forEach(img => {
    img.addEventListener('mouseover', function() {
      const preview = document.createElement('img');
      preview.src = this.src;
      preview.style.position = 'absolute';
      preview.style.zIndex = '9999';
      preview.style.maxWidth = '100px';
      preview.style.border = '1px solid black';
      document.body.appendChild(preview);
      
      const x = event.clientX;
      const y = event.clientY;
      preview.style.left = `${x}px`;
      preview.style.top = `${y}px`;
      
      img.addEventListener('mouseout', function() {
        document.body.removeChild(preview);
      });
    });
  });

  // navigation.js
document.addEventListener('DOMContentLoaded', function() {
    const navLinks = document.querySelectorAll('.nav-link');
    const currentPath = window.location.pathname;

    navLinks.forEach(link => {
        if (link.href === currentPath) {
            link.classList.add('active');
        }
    });
});