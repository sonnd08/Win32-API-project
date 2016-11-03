using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sprite_UserControl
{


    public partial class ucSprite : UserControl
    {


        public ucSprite()
        {
            InitializeComponent();
        }

        List<_SPRITE_CONTROL> SpriteSheet;
        int iSheetSize = 1;

        private void timerSpriteRefreshRate_Tick(object sender, EventArgs e)
        {
            for (int i = 0; i < SpriteSheet.Count; i++)
            {
                //SpriteSheet[i].Update();
                this.Refresh();
            }
        }

        private void ucSprite_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < SpriteSheet.Count; i++)
            {
                SpriteSheet[i].draw(e.Graphics);
            }
        }

        private void ucSprite_Load(object sender, EventArgs e)
        {
            SpriteSheet = new List<_SPRITE_CONTROL>();
            Bitmap[] bmp;
            bmp = new Bitmap[6];

            bmp[0] = Properties.Resources.effect_head_0;
            bmp[1] = Properties.Resources.effect_head_1;
            bmp[2] = Properties.Resources.effect_head_2;
            bmp[3] = Properties.Resources.effect_head_3;
            bmp[4] = Properties.Resources.effect_head_4;
            bmp[5] = Properties.Resources.effect_head_5;

            for (int i = 0; i < iSheetSize; i++)
            {
                SpriteSheet.Add(new _SPRITE_CONTROL(bmp, 0, 0));
            }
        }
    }
}
